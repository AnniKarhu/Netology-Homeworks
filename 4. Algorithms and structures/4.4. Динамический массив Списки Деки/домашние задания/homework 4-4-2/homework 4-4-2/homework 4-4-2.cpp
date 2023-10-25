// homework 4-4-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <string>

#include "Dynamic_array.h"

int get_int_value(const std::string str); //получить от пользователя число типа int
void print_my_dynamic_array(Dynamic_array* arr); //вывести на экран значения динамического массива - класса
void print_dynamic_array(int* arr, int logical_size, int actual_size); //вывести на экран значения простого динамического массива 
void enlarge_simple_array_size_x2(int* &arr,  int& arr_actual_size, const int arr_logical_size); //увеличить фактический размер массива в 2 раза
void append_to_dynamic_array(int* &arr,  const int new_value, int& arr_actual_size, int& arr_logical_size); //добавить еще один элемент к существующему массиву

int main()
{
    setlocale(LC_ALL, "rus");

    Dynamic_array* my_dynamic_array = new Dynamic_array(); //класс обертка для работы с динамическим массивом

    //получить от пользователя фактический размер
    int arr_actual_size = get_int_value("Введите фактичеcкий размер массива: ");
    while (!my_dynamic_array->set_actual_size(arr_actual_size))
    {
        arr_actual_size = get_int_value("Введите фактичеcкий размер массива: ");
    }

    int* simple_int_array = new int[arr_actual_size] {}; //простой динамический массив    

    //получить от пользователя логический размер
    int arr_logical_size = get_int_value("Введите логический размер массива: ");
    while (!my_dynamic_array->set_logical_size(arr_logical_size))
    {
        arr_logical_size = get_int_value("Введите логический размер массива: ");
    }

    //получить от пользователя значения элементов массива
    for (int i = 0; i < my_dynamic_array->get_logical_size(); ++i)
    {
        int new_value = get_int_value("Введите arr[" + std::to_string(i) + "]: ");
        if (!my_dynamic_array->add_array_element(i, new_value))
        {
            std::cout << "Ошибка ввода элемента массива my_dynamic_array\n";
        }

        if (i < arr_logical_size)
        {
            simple_int_array[i] = new_value;
        }
        else
        {
            std::cout << "Ошибка ввода элемента массива simple_int_array\n";
        }
    }

    //вывести на экран значения элементов массива
    std::cout << "Динамический массив-класс: ";
    print_my_dynamic_array(my_dynamic_array); //вывести на экран значения динамического массива-класса
    std::cout << "\n";
    std::cout << "Простой динамический массив: ";
    print_dynamic_array(simple_int_array, arr_logical_size, arr_actual_size); //вывести на экран значения простого динамического массива 
    std::cout << "\n";

    //получить от пользователя новый элемент для добавления в массив
    int new_value = get_int_value("Введите элемент для добавления или 0 для выхода: ");
    while (new_value)
    {
        my_dynamic_array->append_to_dynamic_array(new_value); //добавление нового элемента в массив-класс
          
        //добавление элемента в простой массив
        append_to_dynamic_array(simple_int_array, new_value, arr_actual_size, arr_logical_size); //добавить еще один элемент к существующему массиву
    

        //вывести значения на экран
        std::cout << "Динамический массив-класс: ";
        print_my_dynamic_array(my_dynamic_array); //вывести на экран значения динамического массива-класса
        std::cout << "\n";
        std::cout << "Простой динамический массив: ";
        print_dynamic_array(simple_int_array, arr_logical_size, arr_actual_size); //вывести на экран значения простого динамического массива
        std::cout << "\n";

        new_value = get_int_value("Введите элемент для добавления или 0 для выхода: "); //получить от пользователя новый элемент для добавления в массив
     }
    
    std::cout << "Спасибо! Ваш массив-класс: ";
    print_my_dynamic_array(my_dynamic_array); //вывести на экран значения динамического массива-класса
    std::cout << "\n";
    std::cout << "Спасибо! Ваш простой массив: ";
    print_dynamic_array(simple_int_array, arr_logical_size, arr_actual_size); //вывести на экран значения простого динамического массива

    delete my_dynamic_array;   
    delete[] simple_int_array;

}

int get_int_value(const std::string str) //получить от пользователя число типа int
{
    std::cout << str;
    int temp_value;
    std::cin >> temp_value;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << str;
        std::cin >> temp_value;
    }

    return temp_value;
}

void print_my_dynamic_array(Dynamic_array* arr) //вывести на экран значения динамического массива-класса
{
    //значения логической части
    for (int i = 0; i < arr->get_logical_size(); ++i)
    {
        bool temp_result = false;
        int temp_value = arr->get_array_element(i, temp_result);
        if (temp_result)
        {
            std::cout << temp_value << " ";
        }
        else
        {
            std::cout << "? ";
        }
    }

    //значения запаса
    for (int i = arr->get_logical_size(); i < arr->get_actual_size(); ++i)
    {
        std::cout << "_ ";
    }
}

void print_dynamic_array(int* arr, int logical_size, int actual_size) //вывести на экран значения простого динамического массива 
{
    //значения логической части
    for (int i = 0; i < logical_size; ++i)
    {
        std::cout << arr[i] << " ";
    }

    //значения запаса
    for (int i = logical_size; i < actual_size; ++i)
    {
        std::cout << "_ ";
    }
}

void enlarge_simple_array_size_x2(int* &arr, int& arr_actual_size,  const int arr_logical_size) //увеличить фактический размер массива в 2 раза
{
    //организовать новый массив в 2 раза больше предыдущего
    arr_actual_size *= 2;
    int* new_arr = new int[arr_actual_size];

    //скопировать элементы из старого массива
    for (int i = 0; i < arr_logical_size; ++i)
    {
        new_arr[i] = arr[i];
    }
    delete[] arr;  //освободить память старого массива 
    arr = new_arr; //переназначить указатель
}

void append_to_dynamic_array(int* &arr,  const int new_value, int& arr_actual_size,  int& arr_logical_size) //добавить еще один элемент к существующему массиву
{
    if (arr_actual_size == arr_logical_size) //массив полностью заполнен, запаса нет
    {
        enlarge_simple_array_size_x2(arr,  arr_actual_size, arr_logical_size); //увеличить фактический размер массива в 2 раза        
    }

    arr[arr_logical_size] = new_value;
    ++arr_logical_size;
}