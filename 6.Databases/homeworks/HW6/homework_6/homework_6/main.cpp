#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
#include <Windows.h>

#include "bookshop_tables.h"
#include "db_bookshop.h"

#pragma execution_character_set("utf-8")

int main()
{
	//setlocale(LC_ALL, "rus");

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	try
	{
		std::string connection_str = "host=127.0.0.1 "
		"port=5432 "
		"dbname=db_homework06 "
		"user=postgres "
		"password=gjcnuhtc";

		DB_bookshop db_mybookshop(connection_str);
		
		if (db_mybookshop.start_db())
		{
			std::cout << "Добро пожаловать в базу данных книжных магазинов.\n";	
			//std::cout << "В нашей базе имеются следующие издательства:\n";
			//db_mybookshop.print_publishers();
			//std::cout <<   "Введите номер издательства, информацию по которому Вы хотите получить:\n";
			
			int user_choice = db_mybookshop.get_publisher_num_from_user();
			std::cout << db_mybookshop.get_publisher_name_by_num(user_choice) << "\n";
			
			//инкрементировать итератор  user_choice раз и получить название издательства
			//
			//	далее по названию получить указатель на конкретное издательство и определить, в каких магазинах есть книги
			
			
		}
		else
		{
			std::cout << "Не удалось подключиться к базе данных. Дальнейшая работа невозможна, программа будет закрыта.\n";
			return 0;
		}

	}
	catch (const std::exception& ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
	}
	





	return 0;
}