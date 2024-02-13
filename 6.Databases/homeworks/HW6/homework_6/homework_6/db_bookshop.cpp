#include "db_bookshop.h"
#include "bookshop_tables.h"

#pragma execution_character_set("utf-8") //без этой строки кириллические строки в базу данных не попадают - вываливается ошибка базы данных при попытке отправить в базу данные с кириллицей

DB_bookshop::DB_bookshop(const std::string params_str)  noexcept : connection_str{ params_str }
{

}

DB_bookshop::~DB_bookshop()
{
	//
}

bool DB_bookshop::connect_db() //выполнить подключение к БД
{
	try //при проблеме с подключением выбрасывает исключение
	{
		connection_ptr = std::make_unique<Wt::Dbo::backend::Postgres>(connection_str);
		session.setConnection(std::move(connection_ptr)); //связь между сессией и подключением

		//привязать созданный ORM-класс к сессии
		session.mapClass<Publisher>("publisher"); //в кавычках - название таблицы - в этом примере - publisher	(Класс Publisher описывает таблицу publisher)
		session.mapClass<Book>("book");
		session.mapClass<Stock>("stock");
		session.mapClass<Sale>("sale");
		session.mapClass<Shop>("shop");

		return true;
	}
	catch (const std::exception& ex)
	{
		last_error = ex.what();
		return false;
	}	
}

bool DB_bookshop::create_tables() //создать необходимые таблицы
{
	bool result = false;
	
	try
	{
		session.createTables(); //попытка создать таблицу - если таблица уже создана, произойдет исключение
		result = true;
	}
	catch (...)
	{
		last_error =  "Таблицы не созданы. Возможно, они  уже существуют";
	}

	return result;
}


bool DB_bookshop::start_db() //начало работы с базой данных
{
	bool result = false;

	if (connect_db()) //подключиться к базе
	{
		result = true;
		if (create_tables())  //создать необходимые таблицы
		{
			//внесение тестовых данных в базу
			insert_test_data();
		}
		else
		{
			print_last_error(); //вывести информацию о последней ошибке
		}
		
	}

	return result;
}

std::string DB_bookshop::get_last_error_desc() //получить описание последней возникшей ошибки
{
	return last_error;
}

void DB_bookshop::print_last_error() //вывести информацию о последней ошибке
{
	std::cout << "Последняя ошибка: " << last_error << "\n";
}

void DB_bookshop::print_publishers() //вывести все имеющиеся издательства
{
	Wt::Dbo::Transaction tr_add_data{ session };
	auto data = session.find<Publisher>().resultList();

	int len = data.size();
	auto it = data.begin();

	for (int i = 0; i<len; ++it, ++i)
	//for (auto& elem : data)
	{
		std::cout << i+1 << ": " << (*it)->publisher_name << "\n";
		//std::cout << elem->publisher_name << "\n";
	}

	tr_add_data.commit();
}

int DB_bookshop::get_publisher_num_from_user() //получить от пользлвателя номер издательства
{	
	Wt::Dbo::Transaction tr_add_data{ session };
	auto data = session.find<Publisher>().resultList();

	int len = data.size();
	if (len == 0)
	{
		std::cout << "В нашей базе пока нет ни одного издательства. Приходите попозже.\n";
		tr_add_data.commit();
		return -1;
	}	
	
	int user_choice = -1;
	while (user_choice < 0)
	{
		std::cout << "В нашей базе имеются следующие издательства:\n";
		auto it = data.begin();

		for (int i = 0; i < len; ++it, ++i)
		{
			std::cout << i + 1 << ": " << (*it)->publisher_name << "\n";		
		}
		std::cout << "\n";

		std::cout << "Введите номер издательства, информацию по которому Вы хотите получить или 0 для выхода:\n";
		std::cin >> user_choice;
		if (std::cin.fail())  //ошибка ввода			
		{
			user_choice = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Ваш выбор непонятен.\n\n";
			data = session.find<Publisher>().resultList();
		}
	}
	
	tr_add_data.commit();
	return user_choice;
}

std::string DB_bookshop::get_publisher_name_by_num(int num) //получить название издательства по его порядковому номеру в базе
{
	
	где-то тут вылетает
	std::string res_name; 

	Wt::Dbo::Transaction tr_add_data{ session };
	auto data = session.find<Publisher>().resultList();

	int len = data.size();
	if ((len == 0) ||  //в базе нет записей
	   (num > len) ||  //неверный номер записи
	   (num <= 0))
	{
		tr_add_data.commit();
		return res_name;
	}

	auto it = data.begin();
	for (int i = 0; i < num -1; ++i)
	{
		++it;
	} 

	res_name = (*it)->publisher_name;
	
	tr_add_data.commit();

}

void DB_bookshop::insert_test_data() //внести данные в таблицы
{
	Wt::Dbo::Transaction tr_add_data{ session };
	
	//издательства
	std::unique_ptr<Publisher> publisher_1{ new Publisher{"Издательство самообразование"}}; 
	std::unique_ptr<Publisher> publisher_2{ new Publisher{"Издательство уютный дом"}};
	std::unique_ptr<Publisher> publisher_3{ new Publisher{"Издательство новые детские книги"}};
	std::unique_ptr<Publisher> publisher_4{ new Publisher{"Издательство мир фантастики"}};

	auto ptr_publisher_1 = session.add<Publisher>(std::move(publisher_1));
	auto ptr_publisher_2 = session.add<Publisher>(std::move(publisher_2));
	auto ptr_publisher_3 = session.add<Publisher>(std::move(publisher_3));
	auto ptr_publisher_4 = session.add<Publisher>(std::move(publisher_4));

	//магазины
	std::unique_ptr<Shop> shop_1{ new Shop{"Самый центральный магазин"}};  
	std::unique_ptr<Shop> shop_2{ new Shop{"Магазин полезной книги"}};
	std::unique_ptr<Shop> shop_3{ new Shop{"Магазин детских товаров"}};
	std::unique_ptr<Shop> shop_4{ new Shop{"Онлайн магазин книг"}};

	auto ptr_shop_1 = session.add<Shop>(std::move(shop_1));
	auto ptr_shop_2 = session.add<Shop>(std::move(shop_2));
	auto ptr_shop_3 = session.add<Shop>(std::move(shop_3));
	auto ptr_shop_4 = session.add<Shop>(std::move(shop_4));

	//книги
	std::unique_ptr<Book> publ_1_book1 = std::make_unique<Book>();
	publ_1_book1->title = "Невероятные приключения нетипизированных указателей в многомерных массивах";
	publ_1_book1->publisher = ptr_publisher_1;
	auto ptr_publ_1_book1 = session.add<Book>(std::move(publ_1_book1));

	std::unique_ptr<Book> publ_1_book2 = std::make_unique<Book>();
	publ_1_book2->title = "Самоучитель по вышиванию верблюдов";
	publ_1_book2->publisher = ptr_publisher_1;
	auto ptr_publ_1_book2 = session.add<Book>(std::move(publ_1_book2));

	std::unique_ptr<Book> publ_1_book3 = std::make_unique<Book>();
	publ_1_book3->title = "Квантовая физика для 2-го класса";
	publ_1_book3->publisher = ptr_publisher_1;
	auto ptr_publ_1_book3 = session.add<Book>(std::move(publ_1_book3));

	std::unique_ptr<Book> publ_1_book4 = std::make_unique<Book>();
	publ_1_book4->title = "Дрессировка крокодилов для начинающих";
	publ_1_book4->publisher = ptr_publisher_1;
	auto ptr_publ_1_book4 = session.add<Book>(std::move(publ_1_book4));

	std::unique_ptr<Book> publ_1_book5 = std::make_unique<Book>();
	publ_1_book5->title = "Вреднология - полный курс. Теория и практические задания";
	publ_1_book5->publisher = ptr_publisher_1;
	auto ptr_publ_1_book5 = session.add<Book>(std::move(publ_1_book5));

	std::unique_ptr<Book> publ_1_book6 = std::make_unique<Book>();
	publ_1_book6->title = "Китайский за 10 дней. Букварь.";
	publ_1_book6->publisher = ptr_publisher_1;
	auto ptr_publ_1_book6 = session.add<Book>(std::move(publ_1_book6));

	std::unique_ptr<Book> publ_2_book1 = std::make_unique<Book>();
	publ_2_book1->title = "Как приготовить крякозябру - настольная книга рецептов";
	publ_2_book1->publisher = ptr_publisher_2;
	auto ptr_publ_2_book1 = session.add<Book>(std::move(publ_2_book1));

	std::unique_ptr<Book> publ_2_book2 = std::make_unique<Book>();
	publ_2_book2->title = "Двадцать простых выкроек для костюма Чебурашки";
	publ_2_book2->publisher = ptr_publisher_2;
	auto ptr_publ_2_book2 = session.add<Book>(std::move(publ_2_book2));

	std::unique_ptr<Book> publ_2_book3 = std::make_unique<Book>();
	publ_2_book3->title = "Пингвин в вашем доме - все о разведении и содержании";
	publ_2_book3->publisher = ptr_publisher_2;
	auto ptr_publ_2_book3 = session.add<Book>(std::move(publ_2_book3));

	std::unique_ptr<Book> publ_2_book4 = std::make_unique<Book>();
	publ_2_book4->title = "Крокодил в вашем доме - все о разведении и содержании";
	publ_2_book4->publisher = ptr_publisher_2;
	auto ptr_publ_2_book4 = session.add<Book>(std::move(publ_2_book4));

	std::unique_ptr<Book> publ_3_book1 = std::make_unique<Book>();
	publ_3_book1->title = "Посадка и сбор репки - полная хронология событий";
	publ_3_book1->publisher = ptr_publisher_3;
	auto ptr_publ_3_book1 = session.add<Book>(std::move(publ_3_book1));

	std::unique_ptr<Book> publ_3_book2 = std::make_unique<Book>();
	publ_3_book2->title = "Колобок против Курочки Рябы";
	publ_3_book2->publisher = ptr_publisher_3;
	auto ptr_publ_3_book2 = session.add<Book>(std::move(publ_3_book2));

	std::unique_ptr<Book> publ_3_book3 = std::make_unique<Book>();
	publ_3_book3->title = "Крокодил и семеро козлят";
	publ_3_book3->publisher = ptr_publisher_3;
	auto ptr_publ_3_book3 = session.add<Book>(std::move(publ_3_book3));

	std::unique_ptr<Book> publ_4_book1 = std::make_unique<Book>();
	publ_4_book1->title = "Драконы за плинтусом";
	publ_4_book1->publisher = ptr_publisher_4;
	auto ptr_publ_4_book1 = session.add<Book>(std::move(publ_4_book1));

	std::unique_ptr<Book> publ_4_book2 = std::make_unique<Book>();
	publ_4_book2->title = "Монстрология - полное собрание тварей";
	publ_4_book2->publisher = ptr_publisher_4;
	auto ptr_publ_4_book2 = session.add<Book>(std::move(publ_4_book2));

	std::unique_ptr<Book> publ_4_book3 = std::make_unique<Book>();
	publ_4_book3->title = "Новые приключения Симплозябры.";
	publ_4_book3->publisher = ptr_publisher_4;
	auto ptr_publ_4_book3 = session.add<Book>(std::move(publ_4_book3));

	std::unique_ptr<Book> publ_4_book4 = std::make_unique<Book>();
	publ_4_book4->title = "Симплозябра - великое космическое путешествие.";
	publ_4_book4->publisher = ptr_publisher_4;
	auto ptr_publ_4_book4 = session.add<Book>(std::move(publ_4_book4));

	//запасы
	//ptr_shop_1 "Самый центральный магазин"
	//"Невероятные приключения нетипизированных указателей в многомерных массивах"
	std::unique_ptr<Stock> publ1_book1_shop1 = std::make_unique<Stock>();
	publ1_book1_shop1->book = ptr_publ_1_book1;
	publ1_book1_shop1->shop = ptr_shop_1;
	publ1_book1_shop1->count = 12;
	auto ptr_publ1_book1_shop1 = session.add<Stock>(std::move(publ1_book1_shop1));

	//"Самоучитель по вышиванию верблюдов"
	std::unique_ptr<Stock> publ1_book2_shop1 = std::make_unique<Stock>();
	publ1_book2_shop1->book = ptr_publ_1_book2;
	publ1_book2_shop1->shop = ptr_shop_1;
	publ1_book2_shop1->count = 15;
	auto ptr_publ1_book2_shop1 = session.add<Stock>(std::move(publ1_book2_shop1));
	
	//"Квантовая физика для 2-го класса"
	std::unique_ptr<Stock> publ1_book3_shop1 = std::make_unique<Stock>();
	publ1_book3_shop1->book = ptr_publ_1_book3;
	publ1_book3_shop1->shop = ptr_shop_1;
	publ1_book3_shop1->count = 5;
	auto ptr_publ1_book3_shop1 = session.add<Stock>(std::move(publ1_book3_shop1));

	//"Дрессировка крокодилов для начинающих"
	std::unique_ptr<Stock> publ1_book4_shop1 = std::make_unique<Stock>();
	publ1_book4_shop1->book = ptr_publ_1_book4;
	publ1_book4_shop1->shop = ptr_shop_1;
	publ1_book4_shop1->count = 20;
	auto ptr_publ1_book4_shop1 = session.add<Stock>(std::move(publ1_book4_shop1));

	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Stock> publ1_book5_shop1 = std::make_unique<Stock>();
	publ1_book5_shop1->book = ptr_publ_1_book5;
	publ1_book5_shop1->shop = ptr_shop_1;
	publ1_book5_shop1->count = 23;
	auto ptr_publ1_book5_shop1 = session.add<Stock>(std::move(publ1_book5_shop1));

	//"Китайский за 10 дней. Букварь."
	std::unique_ptr<Stock> publ1_book6_shop1 = std::make_unique<Stock>();
	publ1_book6_shop1->book = ptr_publ_1_book6;
	publ1_book6_shop1->shop = ptr_shop_1;
	publ1_book6_shop1->count = 4;
	auto ptr_publ1_book6_shop1 = session.add<Stock>(std::move(publ1_book6_shop1));

	//"Как приготовить крякозябру - настольная книга рецептов"
	std::unique_ptr<Stock> publ2_book1_shop1 = std::make_unique<Stock>();
	publ2_book1_shop1->book = ptr_publ_2_book1;
	publ2_book1_shop1->shop = ptr_shop_1;
	publ2_book1_shop1->count = 45;
	auto ptr_publ2_book1_shop1 = session.add<Stock>(std::move(publ2_book1_shop1));

	//"Двадцать простых выкроек для костюма Чебурашки"
	std::unique_ptr<Stock> publ2_book2_shop1 = std::make_unique<Stock>();
	publ2_book2_shop1->book = ptr_publ_2_book2;
	publ2_book2_shop1->shop = ptr_shop_1;
	publ2_book2_shop1->count = 10;
	auto ptr_publ2_book2_shop1 = session.add<Stock>(std::move(publ2_book2_shop1));

	//"Пингвин в вашем доме - все о разведении и содержании"
	std::unique_ptr<Stock> publ2_book3_shop1 = std::make_unique<Stock>();
	publ2_book3_shop1->book = ptr_publ_2_book3;
	publ2_book3_shop1->shop = ptr_shop_1;
	publ2_book3_shop1->count = 15;
	auto ptr_publ2_book3_shop1 = session.add<Stock>(std::move(publ2_book3_shop1));

	//"Крокодил в вашем доме - все о разведении и содержании"
	std::unique_ptr<Stock> publ2_book4_shop1 = std::make_unique<Stock>();
	publ2_book4_shop1->book = ptr_publ_2_book4;
	publ2_book4_shop1->shop = ptr_shop_1;
	publ2_book4_shop1->count = 15;
	auto ptr_publ2_book4_shop1 = session.add<Stock>(std::move(publ2_book4_shop1));

	//"Посадка и сбор репки - полная хронология событий"
	std::unique_ptr<Stock> publ3_book1_shop1 = std::make_unique<Stock>();
	publ3_book1_shop1->book = ptr_publ_3_book1;
	publ3_book1_shop1->shop = ptr_shop_1;
	publ3_book1_shop1->count = 7;
	auto ptr_publ3_book1_shop1 = session.add<Stock>(std::move(publ3_book1_shop1));

	//"Колобок против Курочки Рябы"
	std::unique_ptr<Stock> publ3_book2_shop1 = std::make_unique<Stock>();
	publ3_book2_shop1->book = ptr_publ_3_book1;
	publ3_book2_shop1->shop = ptr_shop_1;
	publ3_book2_shop1->count = 10;
	auto ptr_publ3_book2_shop1 = session.add<Stock>(std::move(publ3_book2_shop1));

	//"Крокодил и семеро козлят"
	std::unique_ptr<Stock> publ3_book3_shop1 = std::make_unique<Stock>();
	publ3_book3_shop1->book = ptr_publ_3_book1;
	publ3_book3_shop1->shop = ptr_shop_1;
	publ3_book3_shop1->count = 12;
	auto ptr_publ3_book3_shop1 = session.add<Stock>(std::move(publ3_book3_shop1));

	//"Драконы за плинтусом"
	std::unique_ptr<Stock> publ4_book1_shop1 = std::make_unique<Stock>();
	publ4_book1_shop1->book = ptr_publ_4_book1;
	publ4_book1_shop1->shop = ptr_shop_1;
	publ4_book1_shop1->count = 34;
	auto ptr_publ4_book1_shop1 = session.add<Stock>(std::move(publ4_book1_shop1));

	//"Монстрология - полное собрание тварей"
	std::unique_ptr<Stock> publ4_book2_shop1 = std::make_unique<Stock>();
	publ4_book2_shop1->book = ptr_publ_4_book2;
	publ4_book2_shop1->shop = ptr_shop_1;
	publ4_book2_shop1->count = 23;
	auto ptr_publ4_book2_shop1 = session.add<Stock>(std::move(publ4_book2_shop1));

	//"Новые приключения Симплозябры."
	std::unique_ptr<Stock> publ4_book3_shop1 = std::make_unique<Stock>();
	publ4_book3_shop1->book = ptr_publ_4_book3;
	publ4_book3_shop1->shop = ptr_shop_1;
	publ4_book3_shop1->count = 10;
	auto ptr_publ4_book3_shop1 = session.add<Stock>(std::move(publ4_book3_shop1));

	//"Симплозябра - великое космическое путешествие."
	std::unique_ptr<Stock> publ4_book4_shop1 = std::make_unique<Stock>();
	publ4_book4_shop1->book = ptr_publ_4_book1;
	publ4_book4_shop1->shop = ptr_shop_1;
	publ4_book4_shop1->count = 10;
	auto ptr_publ4_book4_shop1 = session.add<Stock>(std::move(publ4_book4_shop1));

	//ptr_shop_2 "Магазин полезной книги"
	// "Самоучитель по вышиванию верблюдов"
	std::unique_ptr<Stock> publ1_book2_shop2 = std::make_unique<Stock>();
	publ1_book2_shop2->book = ptr_publ_2_book2;
	publ1_book2_shop2->shop = ptr_shop_2;
	publ1_book2_shop2->count = 5;
	auto ptr_publ1_book2_shop2 = session.add<Stock>(std::move(publ1_book2_shop2));

	//"Квантовая физика для 2-го класса"
	std::unique_ptr<Stock> publ1_book3_shop2 = std::make_unique<Stock>();
	publ1_book3_shop2->book = ptr_publ_1_book3;
	publ1_book3_shop2->shop = ptr_shop_2;
	publ1_book3_shop2->count = 12;
	auto ptr_publ1_book3_shop2 = session.add<Stock>(std::move(publ1_book3_shop2));

	//"Дрессировка крокодилов для начинающих"
	std::unique_ptr<Stock> publ1_book4_shop2 = std::make_unique<Stock>();
	publ1_book4_shop2->book = ptr_publ_1_book4;
	publ1_book4_shop2->shop = ptr_shop_2;
	publ1_book4_shop2->count = 6;
	auto ptr_publ1_book4_shop2 = session.add<Stock>(std::move(publ1_book4_shop2));

	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Stock> publ1_book5_shop2 = std::make_unique<Stock>();
	publ1_book5_shop2->book = ptr_publ_1_book5;
	publ1_book5_shop2->shop = ptr_shop_2;
	publ1_book5_shop2->count = 7;
	auto ptr_publ1_book5_shop2 = session.add<Stock>(std::move(publ1_book5_shop2));

	//"Как приготовить крякозябру - настольная книга рецептов"
	std::unique_ptr<Stock> publ2_book1_shop2 = std::make_unique<Stock>();
	publ2_book1_shop2->book = ptr_publ_2_book1;
	publ2_book1_shop2->shop = ptr_shop_2;
	publ2_book1_shop2->count = 2;
	auto ptr_publ2_book1_shop2 = session.add<Stock>(std::move(publ2_book1_shop2));

	//"Двадцать простых выкроек для костюма Чебурашки"
	std::unique_ptr<Stock> publ2_book2_shop2 = std::make_unique<Stock>();
	publ2_book2_shop2->book = ptr_publ_2_book2;
	publ2_book2_shop2->shop = ptr_shop_2;
	publ2_book2_shop2->count = 1;
	auto ptr_publ2_book2_shop2 = session.add<Stock>(std::move(publ2_book2_shop2));

	//"Пингвин в вашем доме - все о разведении и содержании"
	std::unique_ptr<Stock> publ2_book3_shop2 = std::make_unique<Stock>();
	publ2_book3_shop2->book = ptr_publ_2_book3;
	publ2_book3_shop2->shop = ptr_shop_2;
	publ2_book3_shop2->count = 5;
	auto ptr_publ2_book3_shop2 = session.add<Stock>(std::move(publ2_book3_shop2));

	//"Крокодил в вашем доме - все о разведении и содержании"
	std::unique_ptr<Stock> publ2_book4_shop2 = std::make_unique<Stock>();
	publ2_book4_shop2->book = ptr_publ_2_book1;
	publ2_book4_shop2->shop = ptr_shop_2;
	publ2_book4_shop2->count = 6;
	auto ptr_publ2_book4_shop2 = session.add<Stock>(std::move(publ2_book4_shop2));

	//"Монстрология - полное собрание тварей"
	std::unique_ptr<Stock> publ4_book2_shop2 = std::make_unique<Stock>();
	publ4_book2_shop2->book = ptr_publ_4_book2;
	publ4_book2_shop2->shop = ptr_shop_2;
	publ4_book2_shop2->count = 10;
	auto ptr_publ4_book2_shop2 = session.add<Stock>(std::move(publ4_book2_shop2));

	//ptr_shop_3 "Магазин детских товаров"
	//"Квантовая физика для 2-го класса"
	std::unique_ptr<Stock> publ1_book3_shop3 = std::make_unique<Stock>();
	publ1_book3_shop3->book = ptr_publ_1_book3;
	publ1_book3_shop3->shop = ptr_shop_3;
	publ1_book3_shop3->count = 50;
	auto ptr_publ1_book3_shop3 = session.add<Stock>(std::move(publ1_book3_shop3));

	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Stock> publ1_book5_shop3 = std::make_unique<Stock>();
	publ1_book5_shop3->book = ptr_publ_1_book5;
	publ1_book5_shop3->shop = ptr_shop_3;
	publ1_book5_shop3->count = 40;
	auto ptr_publ1_book5_shop3 = session.add<Stock>(std::move(publ1_book5_shop3));

	//"Посадка и сбор репки - полная хронология событий"
	std::unique_ptr<Stock> publ3_book1_shop3 = std::make_unique<Stock>();
	publ3_book1_shop3->book = ptr_publ_3_book1;
	publ3_book1_shop3->shop = ptr_shop_3;
	publ3_book1_shop3->count = 10;
	auto ptr_publ3_book1_shop3 = session.add<Stock>(std::move(publ3_book1_shop3));

	//"Колобок против Курочки Рябы"
	std::unique_ptr<Stock> publ3_book2_shop3 = std::make_unique<Stock>();
	publ3_book2_shop3->book = ptr_publ_3_book2;
	publ3_book2_shop3->shop = ptr_shop_3;
	publ3_book2_shop3->count = 15;
	auto ptr_publ3_book2_shop3 = session.add<Stock>(std::move(publ3_book2_shop3));

	//"Крокодил и семеро козлят"
	std::unique_ptr<Stock> publ3_book3_shop3 = std::make_unique<Stock>();
	publ3_book3_shop3->book = ptr_publ_3_book3;
	publ3_book3_shop3->shop = ptr_shop_3;
	publ3_book3_shop3->count = 12;
	auto ptr_publ3_book3_shop3 = session.add<Stock>(std::move(publ3_book3_shop3));

	//"Новые приключения Симплозябры."
	std::unique_ptr<Stock> publ4_book3_shop3 = std::make_unique<Stock>();
	publ4_book3_shop3->book = ptr_publ_4_book3;
	publ4_book3_shop3->shop = ptr_shop_3;
	publ4_book3_shop3->count = 3;
	auto ptr_publ4_book3_shop3 = session.add<Stock>(std::move(publ4_book3_shop3));

	//"Симплозябра - великое космическое путешествие."
	std::unique_ptr<Stock> publ4_book4_shop3 = std::make_unique<Stock>();
	publ4_book4_shop3->book = ptr_publ_4_book4;
	publ4_book4_shop3->shop = ptr_shop_3;
	publ4_book4_shop3->count = 5;
	auto ptr_publ4_book4_shop3 = session.add<Stock>(std::move(publ4_book4_shop3));

	//ptr_shop_4 "Онлайн магазин книг"
	//"Невероятные приключения нетипизированных указателей в многомерных массивах"
	std::unique_ptr<Stock> publ1_book1_shop4 = std::make_unique<Stock>();
	publ1_book1_shop4->book = ptr_publ_1_book1;
	publ1_book1_shop4->shop = ptr_shop_4;
	publ1_book1_shop4->count = 13;
	auto ptr_publ1_book1_shop4 = session.add<Stock>(std::move(publ1_book1_shop4));

	//"Квантовая физика для 2-го класса"
	std::unique_ptr<Stock> publ1_book3_shop4 = std::make_unique<Stock>();
	publ1_book3_shop4->book = ptr_publ_1_book3;
	publ1_book3_shop4->shop = ptr_shop_4;
	publ1_book3_shop4->count = 12;
	auto ptr_publ1_book3_shop4 = session.add<Stock>(std::move(publ1_book3_shop4));

	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Stock> publ1_book5_shop4 = std::make_unique<Stock>();
	publ1_book5_shop4->book = ptr_publ_1_book5;
	publ1_book5_shop4->shop = ptr_shop_4;
	publ1_book5_shop4->count = 11;
	auto ptr_publ1_book5_shop4 = session.add<Stock>(std::move(publ1_book5_shop4));

	//"Китайский за 10 дней. Букварь."
	std::unique_ptr<Stock> publ1_book6_shop4 = std::make_unique<Stock>();
	publ1_book6_shop4->book = ptr_publ_1_book6;
	publ1_book6_shop4->shop = ptr_shop_4;
	publ1_book6_shop4->count = 10;
	auto ptr_publ1_book6_shop4 = session.add<Stock>(std::move(publ1_book6_shop4));

	//"Как приготовить крякозябру - настольная книга рецептов"
	std::unique_ptr<Stock> publ2_book1_shop4 = std::make_unique<Stock>();
	publ2_book1_shop4->book = ptr_publ_2_book1;
	publ2_book1_shop4->shop = ptr_shop_4;
	publ2_book1_shop4->count = 8;
	auto ptr_publ2_book1_shop4 = session.add<Stock>(std::move(publ2_book1_shop4));

	//"Пингвин в вашем доме - все о разведении и содержании"
	std::unique_ptr<Stock> publ2_book3_shop4 = std::make_unique<Stock>();
	publ2_book3_shop4->book = ptr_publ_2_book3;
	publ2_book3_shop4->shop = ptr_shop_4;
	publ2_book3_shop4->count = 9;
	auto ptr_publ2_book3_shop4 = session.add<Stock>(std::move(publ2_book3_shop4));

	//"Крокодил в вашем доме - все о разведении и содержании"
	std::unique_ptr<Stock> publ2_book4_shop4 = std::make_unique<Stock>();
	publ2_book4_shop4->book = ptr_publ_2_book4;
	publ2_book4_shop4->shop = ptr_shop_4;
	publ2_book4_shop4->count = 10;
	auto ptr_publ2_book4_shop4 = session.add<Stock>(std::move(publ2_book4_shop4));

	//"Крокодил и семеро козлят"
	std::unique_ptr<Stock> publ3_book3_shop4 = std::make_unique<Stock>();
	publ3_book3_shop4->book = ptr_publ_3_book1;
	publ3_book3_shop4->shop = ptr_shop_4;
	publ3_book3_shop4->count = 11;
	auto ptr_publ3_book3_shop4 = session.add<Stock>(std::move(publ3_book3_shop4));

	//"Драконы за плинтусом"
	std::unique_ptr<Stock> publ4_book1_shop4 = std::make_unique<Stock>();
	publ4_book1_shop4->book = ptr_publ_4_book1;
	publ4_book1_shop4->shop = ptr_shop_1;
	publ4_book1_shop4->count = 12;
	auto ptr_publ4_book1_shop4 = session.add<Stock>(std::move(publ4_book1_shop4));

	//"Монстрология - полное собрание тварей"
	std::unique_ptr<Stock> publ4_book2_shop4 = std::make_unique<Stock>();
	publ4_book2_shop4->book = ptr_publ_4_book2;
	publ4_book2_shop4->shop = ptr_shop_4;
	publ4_book2_shop4->count = 13;
	auto ptr_publ4_book2_shop4 = session.add<Stock>(std::move(publ4_book2_shop4));

	//продажи
	//ptr_shop_1 "Самый центральный магазин"
	//"Невероятные приключения нетипизированных указателей в многомерных массивах"
	std::unique_ptr<Sale> publ1_book1_shop1_sale1 = std::make_unique<Sale>();
	publ1_book1_shop1_sale1->price = 1090;
	publ1_book1_shop1_sale1->date_sale = "2024-01-12";
	publ1_book1_shop1_sale1->stock = ptr_publ1_book1_shop1;
	publ1_book1_shop1_sale1->sale_count = 2;
	session.add<Sale>(std::move(publ1_book1_shop1_sale1));

	std::unique_ptr<Sale> publ1_book1_shop1_sale2 = std::make_unique<Sale>();
	publ1_book1_shop1_sale2->price = 1300;
	publ1_book1_shop1_sale2->date_sale = "2024-01-15";
	publ1_book1_shop1_sale2->stock = ptr_publ1_book1_shop1;
	publ1_book1_shop1_sale2->sale_count = 1;
	session.add<Sale>(std::move(publ1_book1_shop1_sale2));

	//ptr_shop_1 "Самый центральный магазин"
	//"Дрессировка крокодилов для начинающих"
	std::unique_ptr<Sale> publ1_book4_shop1_sale1 = std::make_unique<Sale>();
	publ1_book4_shop1_sale1->price = 520;
	publ1_book4_shop1_sale1->date_sale = "2024-01-10";
	publ1_book4_shop1_sale1->stock = ptr_publ1_book4_shop1;
	publ1_book4_shop1_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ1_book4_shop1_sale1));

	//ptr_shop_1 "Самый центральный магазин"
	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Sale> publ1_book5_shop1_sale1 = std::make_unique<Sale>();
	publ1_book5_shop1_sale1->price = 700;
	publ1_book5_shop1_sale1->date_sale = "2024-01-03";
	publ1_book5_shop1_sale1->stock = ptr_publ1_book5_shop1;
	publ1_book5_shop1_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ1_book5_shop1_sale1));

	//ptr_shop_1 "Самый центральный магазин"
	//"Китайский за 10 дней. Букварь."
	std::unique_ptr<Sale> publ1_book6_shop1_sale1 = std::make_unique<Sale>();
	publ1_book6_shop1_sale1->price = 120;
	publ1_book6_shop1_sale1->date_sale = "2024-01-13";
	publ1_book6_shop1_sale1->stock = ptr_publ1_book6_shop1;
	publ1_book6_shop1_sale1->sale_count = 2;
	session.add<Sale>(std::move(publ1_book6_shop1_sale1));

	std::unique_ptr<Sale> publ1_book6_shop1_sale2 = std::make_unique<Sale>();
	publ1_book6_shop1_sale2->price = 120;
	publ1_book6_shop1_sale2->date_sale = "2024-02-10";
	publ1_book6_shop1_sale2->stock = ptr_publ1_book6_shop1;
	publ1_book6_shop1_sale2->sale_count = 1;
	session.add<Sale>(std::move(publ1_book6_shop1_sale2));

	//ptr_shop_1 "Самый центральный магазин"
	//"Как приготовить крякозябру - настольная книга рецептов"
	std::unique_ptr<Sale> publ2_book1_shop1_sale1 = std::make_unique<Sale>();
	publ2_book1_shop1_sale1->price = 420;
	publ2_book1_shop1_sale1->date_sale = "2024-01-04";
	publ2_book1_shop1_sale1->stock = ptr_publ2_book1_shop1;
	publ2_book1_shop1_sale1->sale_count = 10;
	session.add<Sale>(std::move(publ2_book1_shop1_sale1));

	std::unique_ptr<Sale> publ2_book1_shop1_sale2 = std::make_unique<Sale>();
	publ2_book1_shop1_sale2->price = 420;
	publ2_book1_shop1_sale2->date_sale = "2024-01-07";
	publ2_book1_shop1_sale2->stock = ptr_publ2_book1_shop1;
	publ2_book1_shop1_sale2->sale_count = 4;
	session.add<Sale>(std::move(publ2_book1_shop1_sale2));

	std::unique_ptr<Sale> publ2_book1_shop1_sale3 = std::make_unique<Sale>();
	publ2_book1_shop1_sale3->price = 470;
	publ2_book1_shop1_sale3->date_sale = "2024-01-12";
	publ2_book1_shop1_sale3->stock = ptr_publ2_book1_shop1;
	publ2_book1_shop1_sale3->sale_count = 2;
	session.add<Sale>(std::move(publ2_book1_shop1_sale3));

	// ptr_shop_1 "Самый центральный магазин"
	//"Крокодил в вашем доме - все о разведении и содержании"
	std::unique_ptr<Sale> publ2_book4_shop1_sale1 = std::make_unique<Sale>();
	publ2_book4_shop1_sale1->price = 270;
	publ2_book4_shop1_sale1->date_sale = "2024-01-30";
	publ2_book4_shop1_sale1->stock = ptr_publ2_book4_shop1;
	publ2_book4_shop1_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ2_book4_shop1_sale1));

	//ptr_shop_1 "Самый центральный магазин"
	//"Крокодил и семеро козлят"
	std::unique_ptr<Sale> publ3_book3_shop1_sale1 = std::make_unique<Sale>();
	publ3_book3_shop1_sale1->price = 70;
	publ3_book3_shop1_sale1->date_sale = "2024-01-07";
	publ3_book3_shop1_sale1->stock = ptr_publ3_book3_shop1;
	publ3_book3_shop1_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ3_book3_shop1_sale1));

	//ptr_shop_1 "Самый центральный магазин"
	//"Драконы за плинтусом"
	std::unique_ptr<Sale> publ4_book1_shop1_sale1 = std::make_unique<Sale>();
	publ4_book1_shop1_sale1->price = 670;
	publ4_book1_shop1_sale1->date_sale = "2024-01-07";
	publ4_book1_shop1_sale1->stock = ptr_publ4_book1_shop1;
	publ4_book1_shop1_sale1->sale_count = 7;
	session.add<Sale>(std::move(publ4_book1_shop1_sale1));

	std::unique_ptr<Sale> publ4_book1_shop1_sale2 = std::make_unique<Sale>();
	publ4_book1_shop1_sale2->price = 670;
	publ4_book1_shop1_sale2->date_sale = "2024-01-12";
	publ4_book1_shop1_sale2->stock = ptr_publ4_book1_shop1;
	publ4_book1_shop1_sale2->sale_count = 2;
	session.add<Sale>(std::move(publ4_book1_shop1_sale2));

	std::unique_ptr<Sale> publ4_book1_shop1_sale3 = std::make_unique<Sale>();
	publ4_book1_shop1_sale3->price = 670;
	publ4_book1_shop1_sale3->date_sale = "2024-01-17";
	publ4_book1_shop1_sale3->stock = ptr_publ4_book1_shop1;
	publ4_book1_shop1_sale3->sale_count = 3;
	session.add<Sale>(std::move(publ4_book1_shop1_sale3));

	//ptr_shop_1 "Самый центральный магазин"
	//"Монстрология - полное собрание тварей"
	std::unique_ptr<Sale> publ4_book2_shop1_sale1 = std::make_unique<Sale>();
	publ4_book2_shop1_sale1->price = 2700;
	publ4_book2_shop1_sale1->date_sale = "2024-01-19";
	publ4_book2_shop1_sale1->stock = ptr_publ4_book2_shop1;
	publ4_book2_shop1_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ4_book2_shop1_sale1));

	//ptr_shop_2 "Магазин полезной книги"
	//"Дрессировка крокодилов для начинающих"
	std::unique_ptr<Sale> publ1_book4_shop2_sale1 = std::make_unique<Sale>();
	publ1_book4_shop2_sale1->price = 220;
	publ1_book4_shop2_sale1->date_sale = "2024-01-21";
	publ1_book4_shop2_sale1->stock = ptr_publ1_book4_shop2;
	publ1_book4_shop2_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ1_book4_shop2_sale1));

	//ptr_shop_2 "Магазин полезной книги"
	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Sale> publ1_book5_shop2_sale1 = std::make_unique<Sale>();
	publ1_book5_shop2_sale1->price = 820;
	publ1_book5_shop2_sale1->date_sale = "2024-01-13";
	publ1_book5_shop2_sale1->stock = ptr_publ1_book5_shop2;
	publ1_book5_shop2_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ1_book5_shop2_sale1));


	//ptr_shop_2 "Магазин полезной книги"
	//"Пингвин в вашем доме - все о разведении и содержании"
	std::unique_ptr<Sale> publ2_book3_shop2_sale1 = std::make_unique<Sale>();
	publ2_book3_shop2_sale1->price = 334;
	publ2_book3_shop2_sale1->date_sale = "2024-01-13";
	publ2_book3_shop2_sale1->stock = ptr_publ2_book3_shop2;
	publ2_book3_shop2_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ2_book3_shop2_sale1));

	//ptr_shop_3 "Магазин детских товаров"
	//"Квантовая физика для 2-го класса"
	std::unique_ptr<Sale> publ1_book3_shop3_sale1 = std::make_unique<Sale>();
	publ1_book3_shop3_sale1->price = 415;
	publ1_book3_shop3_sale1->date_sale = "2024-02-03";
	publ1_book3_shop3_sale1->stock = ptr_publ1_book3_shop3;
	publ1_book3_shop3_sale1->sale_count = 15;
	session.add<Sale>(std::move(publ1_book3_shop3_sale1));

	std::unique_ptr<Sale> publ1_book3_shop3_sale2 = std::make_unique<Sale>();
	publ1_book3_shop3_sale2->price = 415;
	publ1_book3_shop3_sale2->date_sale = "2024-02-06";
	publ1_book3_shop3_sale2->stock = ptr_publ1_book3_shop3;
	publ1_book3_shop3_sale2->sale_count = 2;
	session.add<Sale>(std::move(publ1_book3_shop3_sale2));

	//ptr_shop_3 "Магазин детских товаров"
	//"Вреднология - полный курс. Теория и практические задания"
	std::unique_ptr<Sale> publ1_book5_shop3_sale1 = std::make_unique<Sale>();
	publ1_book5_shop3_sale1->price = 655;
	publ1_book5_shop3_sale1->date_sale = "2024-02-10";
	publ1_book5_shop3_sale1->stock = ptr_publ1_book5_shop3;
	publ1_book5_shop3_sale1->sale_count = 4;
	session.add<Sale>(std::move(publ1_book5_shop3_sale1));

	//ptr_shop_3 "Магазин детских товаров"
	//"Колобок против Курочки Рябы"
	std::unique_ptr<Sale> publ3_book2_shop3_sale1 = std::make_unique<Sale>();
	publ3_book2_shop3_sale1->price = 200;
	publ3_book2_shop3_sale1->date_sale = "2024-01-15";
	publ3_book2_shop3_sale1->stock = ptr_publ3_book2_shop3;
	publ3_book2_shop3_sale1->sale_count = 2;
	session.add<Sale>(std::move(publ3_book2_shop3_sale1));

	//ptr_shop_3 "Магазин детских товаров"
	//"Новые приключения Симплозябры."
	std::unique_ptr<Sale> publ4_book3_shop3_sale1 = std::make_unique<Sale>();
	publ4_book3_shop3_sale1->price = 340;
	publ4_book3_shop3_sale1->date_sale = "2024-01-15";
	publ4_book3_shop3_sale1->stock = ptr_publ4_book3_shop3;
	publ4_book3_shop3_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ4_book3_shop3_sale1));

	//ptr_shop_4 "Онлайн магазин книг"
	//"Невероятные приключения нетипизированных указателей в многомерных массивах"
	std::unique_ptr<Sale> publ1_book1_shop4_sale1 = std::make_unique<Sale>();
	publ1_book1_shop4_sale1->price = 1015;
	publ1_book1_shop4_sale1->date_sale = "2024-01-25";
	publ1_book1_shop4_sale1->stock = ptr_publ1_book1_shop4;
	publ1_book1_shop4_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ1_book1_shop4_sale1));

	//ptr_shop_4 "Онлайн магазин книг"
	//"Китайский за 10 дней. Букварь."
	std::unique_ptr<Sale> publ1_book6_shop4_sale1 = std::make_unique<Sale>();
	publ1_book6_shop4_sale1->price = 110;
	publ1_book6_shop4_sale1->date_sale = "2024-01-23";
	publ1_book6_shop4_sale1->stock = ptr_publ1_book6_shop4;
	publ1_book6_shop4_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ1_book6_shop4_sale1));	

	//ptr_shop_4 "Онлайн магазин книг"
	//"Как приготовить крякозябру - настольная книга рецептов"
	std::unique_ptr<Sale> publ2_book1_shop4_sale1 = std::make_unique<Sale>();
	publ2_book1_shop4_sale1->price = 390;
	publ2_book1_shop4_sale1->date_sale = "2024-01-06";
	publ2_book1_shop4_sale1->stock = ptr_publ2_book1_shop4;
	publ2_book1_shop4_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ2_book1_shop4_sale1));

	//ptr_shop_4 "Онлайн магазин книг"
	//"Крокодил и семеро козлят"
	std::unique_ptr<Sale> publ3_book3_shop4_sale1 = std::make_unique<Sale>();
	publ3_book3_shop4_sale1->price = 55;
	publ3_book3_shop4_sale1->date_sale = "2024-01-07";
	publ3_book3_shop4_sale1->stock = ptr_publ3_book3_shop4;
	publ3_book3_shop4_sale1->sale_count = 1;
	session.add<Sale>(std::move(publ3_book3_shop4_sale1));
	
	std::unique_ptr<Sale> publ3_book3_shop4_sale2 = std::make_unique<Sale>();
	publ3_book3_shop4_sale2->price = 65;
	publ3_book3_shop4_sale2->date_sale = "2024-02-06";
	publ3_book3_shop4_sale2->stock = ptr_publ3_book3_shop4;
	publ3_book3_shop4_sale2->sale_count = 1;
	session.add<Sale>(std::move(publ3_book3_shop4_sale2));

	tr_add_data.commit();

}


