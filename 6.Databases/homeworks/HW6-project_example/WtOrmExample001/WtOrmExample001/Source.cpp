#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
#include <Windows.h>

//#pragma execution_character_set("utf-8")

struct Post; //��������������� ���������� ���������, ��� ��� ��� ������ ���� ������������ � ��������� User

struct User
{
	std::string name = "";
	std::string phone = "";
	int karma = 0;
	
	//���� ���� ����� ��� ����� ������ ��� ���������� ��������� many-to-one
	Wt::Dbo::collection<Wt::Dbo::ptr<Post>> posts; //��������� ������ �� ������� post - ��� ������, ������� ����������� ���� ������ //����� ���������� ������ �������, ����� ����� User ������� ��������������� ���������� ��� Post

	//����� �� ������ ������� orm-�����, ����� �������� ��������� ����� persist
	//persist ��������� ���� ���� � �����������
	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::field(a, phone, "phone");
		Wt::Dbo::field(a, karma, "karma");

		//������ ���� ����� ��� ����� ������ ��� ���������� ��������� many-to-one - ����� � ������� �� ��������� Post
		Wt::Dbo::hasMany(a, posts, Wt::Dbo::ManyToOne, "user");
	}
};

//������ ��������� ����� ��� ������������ ������ � ��������� many-to-one
struct Post //�� ������� - ���� User ����� ������� ��������� ������ Post, �� ������ ���� Post ������� ����� ���������� ������ User
{
	std::string title = "";
	std::string text = "";

	Wt::Dbo::ptr<User> user; //��������� �� ������������ user ������ ���� ������
	//persist ��������� ���� ���� � �����������
	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::field(a, text, "text");
		Wt::Dbo::belongsTo(a, user, "user"); //�������� ����� � ������������� �� ������� user

	}
};


int main()
{
	//setlocale(LC_ALL, "rus");

	//2 setlocale ������ �������� �������� ����� � ����� ���������� �� ���� ���� ������
	setlocale(LC_ALL, "rus");
	setlocale(LC_ALL, "UTF8");

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);


	try
	{
		
		//������� ��������������� ����������
		std::string connString = "host=127.0.0.1 "
		"port=5432 "
		"dbname=db_lesson06 "
		"user=lesson06user "
		"password=lesson06user";

		std::unique_ptr<Wt::Dbo::backend::Postgres> connection; //��������� �� ������ "�����������"
		connection = std::make_unique<Wt::Dbo::backend::Postgres>(connString);

		//����� ����� ������� ������ � ��������� �� � �������������� ����������
		Wt::Dbo::Session session; //�������  ������ "������"
		session.setConnection(std::move(connection)); //����� ����� ������� � ������������

		//����� � ������ ����� ��������� ��������� ORM-�����
		session.mapClass<User>("user"); //� �������� - �������� ������� - � ���� ������� - user	(����� User ��������� ������� user)

		//��� ������ ������� ���� �������� ����� - ��� ������������ Many-to-one
		session.mapClass<Post>("post"); //� �������� - �������� ������� - � ���� ������� - post (����� Post ��������� ������� post)

		//mapClass ����� ��������� ��� ���� ������ - ������� ������� � ��������
		
		try
		{
			session.createTables(); //������� ������� ������� - ���� ������� ��� �������, ���������� ����������
		}
		catch (...)
		{
			//setlocale(LC_ALL, "rus");
			std::cout << "������� �� �������. ��������, ���  ��� ����������";
			//���� ������� ��� �������, ��� ���������� ����� ������� ����� � ���������� ���� ����������� ����� �����  catch
		}
		

		//��� �������� ������ � ������� ����� ������� ������������ � �������� � ���
		std::unique_ptr<User> user (new User); //��� ����� make_unique
		user->name = "Steven";
		user->phone = "123456";
		user->karma = 100;

		std::unique_ptr<User> user2 = std::make_unique<User>(); //��� ���� make_unique
		user2->name = "Steven2";
		user2->phone = "123456_2";
		user2->karma = 1002;

		//User ����� ��������� ����� ������ �������������
		std::unique_ptr<User> user3{ new User{"Steven3", "123456_3", 1003} }; //���� ��������� - unique_ptr �� ������ � �����

		//����� ��������� ������ ����������
		Wt::Dbo::Transaction t{ session };
		
		//����� ����� ����� ������������ �������� � ���� ������, ������������ ����� add, � user ���������� ����� move, ��� ��� unique_ptr ��-������� ���������� ������
		session.add<User>(std::move(user));
		

		//session.add ���������� ��������� - ����� ��������� ������������ ������������
		Wt::Dbo::ptr<User> user2_ptr =  session.add<User>(std::move(user2)); //���������� ��������� - ��������� �� ������������ ������ ���� ������
		auto user3_ptr = session.add<User>(std::move(user3)); //���������� ��������� - ��������� �� ������������ ������ ���� ������
		
		//��������� �������� - ����������� ����������
		t.commit();

		//����� ������ �������� ������� ������������ � ���� ������
		std::cout << user3_ptr->name << " has karma " << user3_ptr->karma << std::endl;  //����������� ���������� �� ���� ������

		//����� ����� ������������ �� ��� ��������
		//��� ������ ���� ����� ����������. ���������� ���� ������� t.commite()

		Wt::Dbo::Transaction t2{ session }; //����� ����������
		Wt::Dbo::ptr<User> anotherUserPtr = session.find<User>().where("id = 3");
		std::cout << anotherUserPtr->name << " has karma " << anotherUserPtr->karma << std::endl;  //����������� ���������� �� ���� ������
		
		//��������� ������ ����� ������� ����� �������������� ���� � bind
		int idNumber = 5;
		Wt::Dbo::ptr<User> anotherUserPtr2 = session.find<User>().where("id = ?").bind(idNumber); //�������� �� bind (idNumber ������������� ������ ����� ������� � ��������� where

		//���� ��������� ������� - �� ���� ������ �� ��, � ��������� - ���������� query resaultlist
		auto data = session.find<User>().where("karma > ?").bind(10).resultList();
		//�� ����� ���������� ����� �������������
		for (auto& elem : data)
		{
			std::cout << "User with karma > 10 is: " << elem->name << "\n";
		}

		//����� �� ������, �� ��������� ������ ���� - ������������ resultValue() ������ resultlist()
		try
		{
			auto data2 = session.find<User>().where("karma > ?").bind(100).resultValue(); //���� ������ ���������� ������ ����� ������ - ������� �����������
			std::cout << "User with karma > 100 is: " << data2->name << "\n"; 
		}
		catch(const std::exception & ex)
		{
			std::cout << "\n Error " << ex.what() << "\n";
		}
		
		//����� ��������� ��������� ������� � ������
		auto data3 = session.find<User>().where("karma = ?").bind(100).orWhere("karma = ?").bind(1002).resultList();
		for (auto& elem : data3)
		{
			std::cout << "User with karma > 100 or 1002 is: " << elem->name << "\n";
		}

		auto data4 = session.find<User>().where("karma = ?").bind(1002).orWhere("phone = '123456'").resultList();//���� �� ����� �������� group by � �.�. �������� �� ����� ���
		for (auto& elem : data4)
		{
			std::cout << "User with karma > 1002 or phone = 123456 is: " << elem->name << "\n";
		}

		

		//���������� � ��������� ������ ����� ������ � ������� modify
		auto NewUser = session.find<User>().where("id=?").bind(1).resultValue();
		std::cout << "User name = " << NewUser->name << "\n";
		NewUser.modify()->karma = -10;
		NewUser.modify()->name = "Bill";
		//setlocale(LC_ALL, "UTF8");
		std::cout << "����� ��� New User name = " << NewUser->name << "\n";

		t2.commit(); //��������� ����� �����������


		std::cout << "***********������ ������ Many-to-One********\n";

		//������ ������ Many-to-One

		Wt::Dbo::Transaction t3{ session }; //����� ����������
		std::unique_ptr<User> joe  { new User{"Joe", "123456", 10}};
		std::unique_ptr<User> steve{ new User{"Stevee", "555555", 5} };
		std::unique_ptr<User> mark { new User{"Mark", "000", -5} };

		auto JoeDbPtr =  session.add<User>(move(joe)); //JoeDbPtr - ��������� �� ������������ Joe � ���� ������
		session.add<User>(move(steve));
		session.add<User>(move(mark));		

		//���������� ������
		//������ ����
		std::unique_ptr<Post> post1 = std::make_unique<Post>();
		post1->text = "Hello";
		post1->title = "My first post";
		post1->user = JoeDbPtr; //��������� �� user � ����
		session.add<Post>(move(post1));

		//������ ����
		std::unique_ptr<Post> post2 = std::make_unique<Post>();
		post2->text = "Hello2";
		post2->title = "My first post2";
		post2->user = JoeDbPtr; //��������� �� user � ����
		session.add<Post>(move(post2));		

		t3.commit();
		std::cout << "***********11111********\n";
		
		Wt::Dbo::Transaction t4{ session }; //����� ����������
		//����� ������ � ���������� �����
		Wt::Dbo::ptr<Post> post_found = session.find<Post>().where("id=1");
		std::cout << "���� � ��������� " << post_found->title << " ��� ������� ������������� " << post_found->user->name << "\n";

		//������� ������ ������� ���� ������������?
		//������� �������� ������������
		Wt::Dbo::ptr<User> user_10 = session.find<User>().where("id = 4");
		std::cout << "User " << user_10->name << " ������� " << user_10->posts.size() << " ������:\n"; //user_10->posts - ��� �����
		for (const auto& elem : user_10->posts)
		{
			std::cout << "Title = " << elem->title << "\n"; //������� ��� ��������� ������ �� ���������� ������������
		}

		t4.commit();		

		//����� ������������� ��������� �����
		
		Wt::Dbo::Transaction t5{ session }; //����� ����������

		Wt::Dbo::ptr<User> user_12 = session.find<User>().where("id = 4");

		//������ ����
		std::unique_ptr<Post> post3 = std::make_unique<Post>();
		post3->text = "Hello3";
		post3->title = "My first post3";
		post3->user = user_12; //��������� �� user � ����
		auto post_db_3 = session.add<Post>(move(post3));
		std::cout << "���� � ��������� " << post_db_3->title << " ��� ������� ������������� " << post_db_3->user->name << "\n";
		t5.commit();

		Wt::Dbo::Transaction t6{ session }; //����� ����������
		//�������� ��������� �� ����
		Wt::Dbo::ptr<Post> post_found2 = session.find<Post>().where("id = 1");

		//�������� ��������� �� ������ ������������
		Wt::Dbo::ptr<User> user_11 = session.find<User>().where("id = 2");
		
		post_found2.modify()->user = user_11;
		std::cout << "����� ��������� - ���� � ��������� " << post_found2->title << " ��� ������� ������������� " << post_found2->user->name << "\n";

		t6.commit();

	}	
	catch (const std::exception& ex)
	{
		std::cout << "Error1: " << ex.what() << std::endl;
	}
	

	


	return 0;
}