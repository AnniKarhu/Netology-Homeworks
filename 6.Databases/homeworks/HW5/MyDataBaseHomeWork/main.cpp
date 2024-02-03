#include <iostream>
#include <pqxx/pqxx> 
#include "Windows.h"

#include "data_base.h"
#include "user_interface.h"

//#pragma execution_character_set("utf-8")

int main()
{
	std::cout << "Hello!\n";

	setlocale(LC_ALL, "rus");
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	//system("chcp 1251");

	Data_base my_new_database(
			"host=127.0.0.1 "
			"port=5432 "
			"dbname=db_lesson05 "
			"user=lesson05user "
			"password=lesson05user");
	
	if (my_new_database.start_db())
	{
		std::cout << "db started" << "\n";
	}
	else
	{
		std::cout << "db not started" << "\n";

		my_new_database.print_last_error(); //������� ���������� � ��������� ������
		
		//SetConsoleCP(CP_UTF8);
	    //SetConsoleOutputCP(CP_UTF8);
		//setlocale(LC_ALL, "rus");
		//SetConsoleOutputCP(1251);
	    //SetConsoleCP(1251);

		std::cout << "���������� ������ ����������. ��������� ����� �������.\n";
		return 0;
	}

	try
	{
		//� ������ ���������� � ���� ����� � ���� catch(...) �� �������� - ���������� �������� ��� �������������� � �������� ��������� - ������?
		//������� ���������� - ��������� � �������  �� �������� ���������.
		//�� ����� �� ������ ����� ���������� ���� ���������� � ����� catch(...) ����?
		my_new_database.test_insert();
	}
	catch (...)
	{
		std::cout << "not inserted" << "\n";
	}
	
	int user_choice = 1;
	while (user_choice > 0)
	{
		user_choice = main_menu();
		
		switch (user_choice)
		{
			case 0: 
				std::cout << "�� ��������!\n"; //�����
				//return 0;

			case 1:
				add_new_user(my_new_database); //�������� ������ �������
				break;
		
			case 2: 
				add_user_phone(my_new_database); //�������� ������� ��� ������������� �������
				break;			

			case 3: 
				update_user_data(my_new_database); //�������� ������ � �������
				break;			

			case 4: 
				delete_user_phone(my_new_database); //������� ������� ������� 
				break;
			
			case 5:  
				delete_user(my_new_database); //������� ���������� � �������
				break;			

			case 6:  //����� ������� �� ��� ������ � �����, �������, email ��� ��������
				print_user_info(my_new_database); //����� ���������� � �������
				break;			

			default: 
				std::cout << "����� ����� ���� �� ������������\n";
				user_choice = -1;
				break;			
		}
	}

return 0;
}


