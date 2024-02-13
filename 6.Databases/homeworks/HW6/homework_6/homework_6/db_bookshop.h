#pragma once

#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

class DB_bookshop
{
private:
	const std::string connection_str; //строка параметров для подключения
	std::unique_ptr<Wt::Dbo::backend::Postgres> connection_ptr; //указатель на объект "подключение"
	

	std::string last_error; //описание последней возникшей ошибки

	bool connect_db(); //выполнить подключение к БД
	bool create_tables(); //создать необходимые таблицы
	void insert_test_data(); //внести данные в таблицы
	

public:
	Wt::Dbo::Session session; //  объект "сессия"
	explicit DB_bookshop(const std::string params_str)  noexcept;
	~DB_bookshop();
	DB_bookshop(const DB_bookshop& other) = delete; //конструктор копирования
	DB_bookshop(DB_bookshop&& other) = delete;	// конструктор перемещения
	DB_bookshop& operator=(const DB_bookshop& other) = delete;  //оператор присваивания 
	DB_bookshop& operator=(DB_bookshop&& other) = delete;       // оператор перемещающего присваивания

	bool start_db(); //начало работы с базой данных
	std::string get_last_error_desc(); //получить описание последней возникшей ошибки
	void print_last_error(); //вывести информацию о последней ошибке
	void print_publishers(); //вывести все имеющиеся издательства
	int get_publisher_num_from_user(); //получить от пользователя номер издательства
	std::string get_publisher_name_by_num(int num); //получить название издательства по его порядковому номеру в базе


};
