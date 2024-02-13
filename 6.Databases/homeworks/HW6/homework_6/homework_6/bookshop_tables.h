#pragma once
#include <iostream>
#include <wt/Dbo/Dbo.h>
#include <Wt/Dbo/backend/Postgres.h>

struct Book;
struct Stock;
struct Sale;
struct Shop;

struct Publisher
{
	std::string	publisher_name;
	
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books; //список книг из таблицы book

	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, publisher_name, "publisher_name");		
		
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");// связь с книгами из структуры Book
	}
}; 

struct Book
{
	std::string	title;
	Wt::Dbo::ptr<Publisher> publisher; //указатель на издателя из таблицы publisher

	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks; //коллекция запасов из таблицы Stock 

	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");

		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");// связь со стоками из структуры Stock

		Wt::Dbo::belongsTo(a, publisher, "publisher"); //указание связи с издательством из таблицы publisher
	}
};

struct Stock
{
	int count;
	Wt::Dbo::ptr<Book> book; //указатель на книгу из таблицы book
	Wt::Dbo::ptr<Shop> shop; //указатель на магазин из таблицы shop
	Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales; //список продаж из таблицы sale

	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, count, "count");

		Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");// связь с продажами из структуры Sale

		Wt::Dbo::belongsTo(a, book, "book"); //указание связи с книгой из таблицы book
		Wt::Dbo::belongsTo(a, shop, "shop"); //указание связи с мазазином из таблицы shop		
	}
};

struct Shop
{
	std::string	shop_name;

	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks; //коллекция запасов из таблицы Stock 	 

	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, shop_name, "shop_name");
		
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");// связь с запасом из структуры Stock		
	}
};



struct Sale
{
	int	price;
	int sale_count;
	std::string	date_sale;
	
	Wt::Dbo::ptr<Stock> stock; //указатель на сток из таблицы stock
	
	template<typename Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, sale_count, "sale_count");
		Wt::Dbo::field(a, date_sale, "date_sale");

		Wt::Dbo::belongsTo(a, stock, "stock"); //указание связи с запасами из таблицы stock
	}
};

