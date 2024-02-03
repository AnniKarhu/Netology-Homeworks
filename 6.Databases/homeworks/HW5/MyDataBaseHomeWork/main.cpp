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

		my_new_database.print_last_error(); //вывести информацию о последней ошибке
		
		//SetConsoleCP(CP_UTF8);
	    //SetConsoleOutputCP(CP_UTF8);
		//setlocale(LC_ALL, "rus");
		//SetConsoleOutputCP(1251);
	    //SetConsoleCP(1251);

		std::cout << "Дальнейшая работа невозможна. Программа будет закрыта.\n";
		return 0;
	}

	try
	{
		//в случае исключения в этом блоке в блок catch(...) не попадаем - исключение проходит как необработанное с падением программы - почему?
		//причина исключения - обращение к объекту  по нулевому указателю.
		//но разве не должно любое исключение быть обработано в блоке catch(...) ниже?
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
				std::cout << "До свидания!\n"; //выход
				//return 0;

			case 1:
				add_new_user(my_new_database); //добавить нового клиента
				break;
		
			case 2: 
				add_user_phone(my_new_database); //добавить телефон для существующего клиента
				break;			

			case 3: 
				update_user_data(my_new_database); //изменить данные о клиенте
				break;			

			case 4: 
				delete_user_phone(my_new_database); //удалить телефон клиента 
				break;
			
			case 5:  
				delete_user(my_new_database); //удалить информацию о клиенте
				break;			

			case 6:  //найти клиента по его данным — имени, фамилии, email или телефону
				print_user_info(my_new_database); //вывод информации о клиенте
				break;			

			default: 
				std::cout << "Такой пункт меню не предусмотрен\n";
				user_choice = -1;
				break;			
		}
	}

return 0;
}


