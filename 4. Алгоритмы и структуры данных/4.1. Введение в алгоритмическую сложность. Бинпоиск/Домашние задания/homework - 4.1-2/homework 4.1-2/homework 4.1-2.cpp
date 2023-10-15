// homework 4.1-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*Вам нужно написать функцию, которая принимает на вход отсортированный массив целых чисел и целое число. Назовём его точкой отсчёта. 
Функция должна посчитать количество элементов в массиве, которые больше, чем переданное в функцию целое число — то есть больше, 
чем точка отсчёта. Требуемая алгоритмическая сложность: время O(log2n), дополнительная память O(1).

Затем нужно протестировать написанную функцию. Точку отсчёта спрашивайте в начале работы программы у пользователя, 
а отсортированный массив сделайте автоматическим, например [14, 16, 19, 32, 32, 32, 56, 69, 72].*/

#include <iostream>
#include "array_exception.h"

int greater_elements_quantity(int* digits_array, int array_size, int reference_point); //количество элементов в массиве, которые больше, чем reference_point

int main()
{
	setlocale(LC_ALL, "rus");

	int digits_array[9] = { 14, 16, 19, 32, 32, 32, 56, 69, 72 };
	int array_size = 9;
	int reference_point;

	while (1)
	{
		std::cout << "Введите точку отсчёта: ";
		std::cin >> reference_point;

		while (std::cin.fail())
		{
			std::cin.clear();

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Введите точку отсчёта:  ";
			std::cin >> reference_point;
		}

		std::cout << "Количество элементов в массиве больших, чем " << reference_point << ": ";

		try 
		{
			std::cout << greater_elements_quantity(digits_array, array_size, reference_point);
		}
		catch (ArrayException& ex)
		{
			std::cout << ex.what();

		}
		catch (...)
		{
			std::cout << "Неизвестная ошибка\n";
		}

		std::cout << "\n";
	}

}

int greater_elements_quantity(int* digits_array, int array_size, int reference_point)
{
	if (array_size < 0) //вдруг в функцию передали неверный размер массива
	{
		throw ArrayException();
		return -1;
	}
	

	//бинарный поиск индекса числа в упорядоченном массиве
	int left = 0;
	int right = array_size - 1;
	int middle;
	int reference_index = array_size; // = 0;
	
	while (left <= right)
	{

		middle = (left + right) / 2;
		if (digits_array[middle] > reference_point) //точка отсчета левее
		{
			reference_index = middle;
			right = middle - 1;
		}
		else //точка отсчета в этой ячейке или правее
		{
			left = middle + 1;
		}


	}

	return  array_size - reference_index;
	
}