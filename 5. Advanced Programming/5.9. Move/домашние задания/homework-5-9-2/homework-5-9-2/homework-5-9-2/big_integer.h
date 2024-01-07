#pragma once
#include <iostream>
#include <vector>

class big_integer
{
private:
	std::vector<int>* big_vector = nullptr; // = { 0 }; //
	bool value_is_valid() const; // = true; //поле принимает значение false, если число не валидно, например, при создании не была успешно преобразована строка в число
	const int elem_size = 4; //сколько разрядов числа хранит один блок -       элемент big_vector
	int sign = 1; //знак числа
public:
	//std::string str_value = "0";
	
	big_integer(std::string value_str);
	big_integer(const big_integer& other);//конструктор копирования
	big_integer(big_integer&& other) noexcept;	// конструктор перемещения

	~big_integer();
	
	big_integer& operator=(const big_integer& other);  //оператор присваивания 
	big_integer& operator=(big_integer&& other) noexcept;       // оператор перемещающего присваивания
	
	big_integer operator+(const big_integer& other); //оператор сложения
	big_integer operator-(const big_integer& other); //оператор вычитания
	big_integer operator*(const int& other); //оператор умножения

	//bool operator>(const big_integer& other) const;
	bool module_greater(const big_integer& first, const big_integer& second); //сравнение чисел по модулю

	int get_size() const;
	//std::string get_elements(); 
	
	friend std::ostream& operator<<(std::ostream& os, const big_integer& my_big_int); //вывод большого числа
};