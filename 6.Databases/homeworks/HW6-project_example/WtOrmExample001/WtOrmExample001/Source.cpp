#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
#include <Windows.h>

//#pragma execution_character_set("utf-8")

struct Post; //предварительное объявление структуры, так как оно должно быть использовано в структуре User

struct User
{
	std::string name = "";
	std::string phone = "";
	int karma = 0;
	
	//поле ниже нужно для связи таблиц при реализации отношения many-to-one
	Wt::Dbo::collection<Wt::Dbo::ptr<Post>> posts; //коллекция постов из таблицы post - это список, который принадлежит базе данных //чтобы компиляция прошла успешно, нужно перед User сделать предварительное объявление для Post

	//чтобы из класса сделать orm-класс, нужно добавить шаблонный метод persist
	//persist связывает поля базы с переменными
	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::field(a, phone, "phone");
		Wt::Dbo::field(a, karma, "karma");

		//строка ниже нужно для связи таблиц при реализации отношения many-to-one - связь с постами из структуры Post
		Wt::Dbo::hasMany(a, posts, Wt::Dbo::ManyToOne, "user");
	}
};

//вторая структура нужна для демонстрации работы с таблицами many-to-one
struct Post //по легенде - один User может создать несколько постов Post, но каждый пост Post написан одним конкретным юзером User
{
	std::string title = "";
	std::string text = "";

	Wt::Dbo::ptr<User> user; //указатель на пользователя user внутри базы данных
	//persist связывает поля базы с переменными
	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::field(a, text, "text");
		Wt::Dbo::belongsTo(a, user, "user"); //указание связи с пользователем из таблицы user

	}
};


int main()
{
	//setlocale(LC_ALL, "rus");

	//2 setlocale подряд помогают выводить текст в обеих кодировках во всем коде даалее
	setlocale(LC_ALL, "rus");
	setlocale(LC_ALL, "UTF8");

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);


	try
	{
		
		//сначала устанавливается соединение
		std::string connString = "host=127.0.0.1 "
		"port=5432 "
		"dbname=db_lesson06 "
		"user=lesson06user "
		"password=lesson06user";

		std::unique_ptr<Wt::Dbo::backend::Postgres> connection; //указатель на объект "подключение"
		connection = std::make_unique<Wt::Dbo::backend::Postgres>(connString);

		//затем нужно создать сессию и привязать ее к установленному соединению
		Wt::Dbo::Session session; //создать  объект "сессия"
		session.setConnection(std::move(connection)); //связь между сессией и подключением

		//затем к сессии нужно привязать созданный ORM-класс
		session.mapClass<User>("user"); //в кавычках - название таблицы - в этом примере - user	(Класс User описывает таблицу user)

		//для второй таблицы тоже замапаем класс - для демонстрации Many-to-one
		session.mapClass<Post>("post"); //в кавычках - название таблицы - в этом примере - post (класс Post описывает таблицу post)

		//mapClass нужно применить для всех таблиц - связать таблицы с классами
		
		try
		{
			session.createTables(); //попытка создать таблицу - если таблица уже создана, произойдет исключение
		}
		catch (...)
		{
			//setlocale(LC_ALL, "rus");
			std::cout << "Таблица не создана. Возможно, она  уже существует";
			//если таблица уже создана, это исключение будет поймано здесь и выполнение кода продолжится после этого  catch
		}
		

		//для внесения данных в таблицу нужно создать пользователя и работать с ним
		std::unique_ptr<User> user (new User); //или через make_unique
		user->name = "Steven";
		user->phone = "123456";
		user->karma = 100;

		std::unique_ptr<User> user2 = std::make_unique<User>(); //или чере make_unique
		user2->name = "Steven2";
		user2->phone = "123456_2";
		user2->karma = 1002;

		//User можно заполнять через объект инициализации
		std::unique_ptr<User> user3{ new User{"Steven3", "123456_3", 1003} }; //этот указатель - unique_ptr не связан с базой

		//далее создается объект транзакции
		Wt::Dbo::Transaction t{ session };
		
		//затем чтобы этого пользователя добавить в базу данных, используется метод add, а user передается через move, так как unique_ptr по-другому передавать нельзя
		session.add<User>(std::move(user));
		

		//session.add возвращает указатель - можно сохранить добавленного пользователя
		Wt::Dbo::ptr<User> user2_ptr =  session.add<User>(std::move(user2)); //полученный указатель - указывает на пользователя внутри базы данных
		auto user3_ptr = session.add<User>(std::move(user3)); //полученный указатель - указывает на пользователя внутри базы данных
		
		//последнее действие - закоммитить транзакцию
		t.commit();

		//можно читать значения объекта пользователя в базе данных
		std::cout << user3_ptr->name << " has karma " << user3_ptr->karma << std::endl;  //считываение происходит из базы данных

		//можно найти пользователя по его значению
		//для поиска тоже нужна транзакция. Предыдущая была закрыта t.commite()

		Wt::Dbo::Transaction t2{ session }; //новая транзакция
		Wt::Dbo::ptr<User> anotherUserPtr = session.find<User>().where("id = 3");
		std::cout << anotherUserPtr->name << " has karma " << anotherUserPtr->karma << std::endl;  //считываение происходит из базы данных
		
		//параметры поиска можно вводить через вопросительный знак и bind
		int idNumber = 5;
		Wt::Dbo::ptr<User> anotherUserPtr2 = session.find<User>().where("id = ?").bind(idNumber); //значение из bind (idNumber подставляется вместо знака вопроса в параметре where

		//если результат запроса - не одна строка из бд, а несколько - используем query resaultlist
		auto data = session.find<User>().where("karma > ?").bind(10).resultList();
		//по этому результату можно итерироваться
		for (auto& elem : data)
		{
			std::cout << "User with karma > 10 is: " << elem->name << "\n";
		}

		//такой же запрос, но результат строго один - используется resultValue() вместо resultlist()
		try
		{
			auto data2 = session.find<User>().where("karma > ?").bind(100).resultValue(); //если запрос возвращает больше одной строки - выкинет исклюячение
			std::cout << "User with karma > 100 is: " << data2->name << "\n"; 
		}
		catch(const std::exception & ex)
		{
			std::cout << "\n Error " << ex.what() << "\n";
		}
		
		//можно прописать несколько условий в запрос
		auto data3 = session.find<User>().where("karma = ?").bind(100).orWhere("karma = ?").bind(1002).resultList();
		for (auto& elem : data3)
		{
			std::cout << "User with karma > 100 or 1002 is: " << elem->name << "\n";
		}

		auto data4 = session.find<User>().where("karma = ?").bind(1002).orWhere("phone = '123456'").resultList();//сюда же можно добавить group by и т.п. Примеров на леции нет
		for (auto& elem : data4)
		{
			std::cout << "User with karma > 1002 or phone = 123456 is: " << elem->name << "\n";
		}

		

		//информацию в найденной строке можно менять с помощью modify
		auto NewUser = session.find<User>().where("id=?").bind(1).resultValue();
		std::cout << "User name = " << NewUser->name << "\n";
		NewUser.modify()->karma = -10;
		NewUser.modify()->name = "Bill";
		//setlocale(LC_ALL, "UTF8");
		std::cout << "Новое имя New User name = " << NewUser->name << "\n";

		t2.commit(); //изменения нужно подтвердить


		std::cout << "***********теперь работа Many-to-One********\n";

		//теперь работа Many-to-One

		Wt::Dbo::Transaction t3{ session }; //новая транзакция
		std::unique_ptr<User> joe  { new User{"Joe", "123456", 10}};
		std::unique_ptr<User> steve{ new User{"Stevee", "555555", 5} };
		std::unique_ptr<User> mark { new User{"Mark", "000", -5} };

		auto JoeDbPtr =  session.add<User>(move(joe)); //JoeDbPtr - указатель на пользователя Joe в базе данных
		session.add<User>(move(steve));
		session.add<User>(move(mark));		

		//добавление постов
		//первый пост
		std::unique_ptr<Post> post1 = std::make_unique<Post>();
		post1->text = "Hello";
		post1->title = "My first post";
		post1->user = JoeDbPtr; //указатель на user в базе
		session.add<Post>(move(post1));

		//второй пост
		std::unique_ptr<Post> post2 = std::make_unique<Post>();
		post2->text = "Hello2";
		post2->title = "My first post2";
		post2->user = JoeDbPtr; //указатель на user в базе
		session.add<Post>(move(post2));		

		t3.commit();
		std::cout << "***********11111********\n";
		
		Wt::Dbo::Transaction t4{ session }; //новая транзакция
		//вывод данных о конкретном посте
		Wt::Dbo::ptr<Post> post_found = session.find<Post>().where("id=1");
		std::cout << "Пост с названием " << post_found->title << " был написан пользователем " << post_found->user->name << "\n";

		//сколько постов написал один пользователь?
		//сначала получить пользователя
		Wt::Dbo::ptr<User> user_10 = session.find<User>().where("id = 4");
		std::cout << "User " << user_10->name << " написал " << user_10->posts.size() << " постов:\n"; //user_10->posts - все посты
		for (const auto& elem : user_10->posts)
		{
			std::cout << "Title = " << elem->title << "\n"; //вывести все заголовки постов от найденного пользователя
		}

		t4.commit();		

		//можно переназначить владельца поста
		
		Wt::Dbo::Transaction t5{ session }; //новая транзакция

		Wt::Dbo::ptr<User> user_12 = session.find<User>().where("id = 4");

		//третий пост
		std::unique_ptr<Post> post3 = std::make_unique<Post>();
		post3->text = "Hello3";
		post3->title = "My first post3";
		post3->user = user_12; //указатель на user в базе
		auto post_db_3 = session.add<Post>(move(post3));
		std::cout << "Пост с названием " << post_db_3->title << " был написан пользователем " << post_db_3->user->name << "\n";
		t5.commit();

		Wt::Dbo::Transaction t6{ session }; //новая транзакция
		//получить указатель на пост
		Wt::Dbo::ptr<Post> post_found2 = session.find<Post>().where("id = 1");

		//получить указатель на нового пользователя
		Wt::Dbo::ptr<User> user_11 = session.find<User>().where("id = 2");
		
		post_found2.modify()->user = user_11;
		std::cout << "После изменения - Пост с названием " << post_found2->title << " был написан пользователем " << post_found2->user->name << "\n";

		t6.commit();

	}	
	catch (const std::exception& ex)
	{
		std::cout << "Error1: " << ex.what() << std::endl;
	}
	

	


	return 0;
}