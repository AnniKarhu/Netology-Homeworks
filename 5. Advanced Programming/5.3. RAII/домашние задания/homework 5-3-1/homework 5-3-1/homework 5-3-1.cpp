// homework 5-3-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>

#include "smart_array2.h"
#include "array_exception.h"


int main()
{
	setlocale(LC_ALL, "rus");

	//класс Smart_array - при добавлении лишнего элемента выкидывает ошибку
	std::cout << "класс Smart_array - при добавлении лишнего элемента выкидывает ошибку\n";
	try {
		Smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		std::cout << arr.get_element(4) << std::endl;
		std::cout << arr.get_element(5) << std::endl;

	}
	catch (const std::exception& ex) {
		std::cout << "Ошибка:" << ex.what() << std::endl;
		
	}

	//класс Smart_array2 - при добавлении лишнего элемента увеличивает размер массива
	std::cout << "\n\nкласс Smart_array2 - при добавлении лишнего элемента увеличивает размер массива\n";
	try {
		Smart_array2 arr2(2);
		arr2.print_array();
		arr2.add_element(1);
		arr2.print_array();
		arr2.add_element(4);
		arr2.print_array();
		arr2.add_element(155);
		arr2.print_array();
		arr2.add_element(14);
		arr2.print_array();
		arr2.add_element(15);
		arr2.print_array();
		std::cout << arr2.get_element(4) << std::endl;
		std::cout << arr2.get_element(5) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << "Ошибка: " << ex.what() << std::endl;		
	}

}