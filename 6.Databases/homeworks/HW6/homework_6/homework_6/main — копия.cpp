#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>
#include <string>
#include <Windows.h>

//#include "bookshop_tables.h"
#include "db_bookshop.h"

#pragma execution_character_set("utf-8")

int main()
{
	//setlocale(LC_ALL, "rus");

	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	DB_bookshop my_new_database(
		"host=127.0.0.1 "
		"port=5432 "
		"dbname=db_homework06 "
		"user=postgres "
		"password=gjcnuhtc");
		//"user=lesson06user "
		//"password=lesson06user");

	if (my_new_database.start_db())
	{
		std::cout << "db started" << "\n";
		try
		{
			my_new_database.insert_test_data2(); //внести данные в таблицы
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}
		
	}
	else
	{
		std::cout << "db not started" << "\n";

		my_new_database.print_last_error(); //вывести информацию о последней ошибке

		std::cout << "Дальнейшая работа невозможна. Программа будет закрыта.\n";
		return 0;
	}

	




	return 0;
}