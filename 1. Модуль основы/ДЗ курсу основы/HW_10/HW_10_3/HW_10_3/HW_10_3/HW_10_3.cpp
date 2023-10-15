﻿// HW_10_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*Напишите четыре функции:

create_two_dim_array: принимает на вход количество строк и столбцов. Создаёт целочисленный двумерный динамический массив заданной размерности и возвращает указатель на него.
fill_two_dim_array: принимает на вход указатель на двумерный целочисленный массив, количество строк и столбцов в нём. Заполняет полученный массив значениями из таблицы умножения. Таблица не ограничена 10 строками или 10 столбцами. Не возвращает ничего.
print_two_dim_array: принимает на вход указатель на двумерный целочисленный массив, количество строк и столбцов в нём. Выводит полученный массив на консоль. Не возвращает ничего.
delete_two_dim_array: принимает на вход указатель на двумерный целочисленный массив, количество строк и столбцов в нём. Очищает полученный массив. Не возвращает ничего.
Используйте эти функции для организации работы программы, которая спрашивает у пользователя количество строк и столбцов и выводит на консоль таблицу умножения заданной размерности.

Примеры работы программы
Введите количество строк: 10
Введите количество столбцов: 10
Таблица умножения:
 1  2  3  4  5  6  7  8  9  10
 2  4  6  8 10 12 14 16 18  20
 3  6  9 12 15 18 21 24 27  30
 4  8 12 16 20 24 28 32 36  40
 5 10 15 20 25 30 35 40 45  50
 6 12 18 24 30 36 42 48 54  60
 7 14 21 28 35 42 49 56 63  70
 8 16 24 32 40 48 56 64 72  80
 9 18 27 36 45 54 63 72 81  90
10 20 30 40 50 60 70 80 90 100
*/
#include <iostream>

int** create_two_dim_arra(int rows, int cols);
void fill_two_dim_array(int** int_ptr, int rows, int cols);
void print_two_dim_array(int** int_ptr, int rows, int cols);
void delete_two_dim_array(int** int_ptr, int rows, int cols);


int main()
{
	setlocale(LC_ALL, "Russian");

	int rows = 0, cols = 0;

	std::cout << "Введите количество строк: ";
	std::cin >> rows;
	std::cout << "Введите количество столбцов: ";
	std::cin >> cols;

	int** int_ptr = create_two_dim_arra(rows, cols);
	fill_two_dim_array(int_ptr,   rows,  cols);
	print_two_dim_array(int_ptr,  rows, cols);
	delete_two_dim_array(int_ptr, rows, cols);

}

int** create_two_dim_arra(int rows, int cols)
{
	int** int_2_dim_arr = new int*[rows];
	for (int i = 0; i < rows; ++i)
	{
		int_2_dim_arr[i] = new int[cols];
	}

	return int_2_dim_arr;
};
void fill_two_dim_array(int** int_ptr, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
		{
			int_ptr[i][j] = (i + 1) * (j + 1);
		}
};
void print_two_dim_array(int** int_ptr, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			std::cout << int_ptr[i][j] << "\t";
		}

		std::cout << "\n";
	}
		
};

//в функции delete_two_dim_array параметр int cols лишний. Оставила, так как так указано в задании
void delete_two_dim_array(int** int_ptr, int rows, int cols)
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] int_ptr[i];
	}

	delete[] int_ptr;
};

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
