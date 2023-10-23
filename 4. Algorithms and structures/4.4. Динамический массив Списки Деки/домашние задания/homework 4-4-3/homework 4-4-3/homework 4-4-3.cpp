// homework 4-4-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <string>
#include <Windows.h>

#include "Dynamic_array.h"

int get_int_value(const std::string str); //получить от пользователя число типа int
void print_my_dynamic_array(Dynamic_array* arr); //вывести на экран значения динамического массива - класса
void print_dynamic_array(int* arr, int logical_size, int actual_size); //вывести на экран значения простого динамического массива 
void enlarge_simple_array_size_x2(int* arr, int& arr_actual_size, const int arr_logical_size); //увеличить фактический размер массива в 2 раза
void append_to_dynamic_array(int* arr, const int new_value, int& arr_actual_size, int& arr_logical_size); //добавить еще один элемент к существующему массиву
bool user_want_to_delete(); //получить информацию от пользователя - хочет ли удалить первый элемент массива
void remove_dynamic_array_head(int* arr, int& arr_actual_size, int& arr_logical_size); //удалить первый элемент массива

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

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

   //получить информацию от пользователя - хочет ли удалить первый элемент массива
    while (user_want_to_delete()) //пользователь хочет удалить первый элемент
    {      
       if ((arr_logical_size == 0) || //массив  пустой
          (my_dynamic_array->get_logical_size() == 0)) //массив  пустой
          {
              std::cout << "Невозможно удалить первый элемент, так как массив пустой.До свидания!";
              return 0; //выход из программы
          }
    
        my_dynamic_array->remove_dynamic_array_head();
        std::cout << "Динамический массив-класс: ";
        print_my_dynamic_array(my_dynamic_array); //вывести на экран значения динамического массива-класса
        std::cout << "\n";
        remove_dynamic_array_head(simple_int_array, arr_actual_size, arr_logical_size); //удалить первый элемент массива
        std::cout << "Простой динамический массив: ";
        print_dynamic_array(simple_int_array, arr_logical_size, arr_actual_size); //вывести на экран значения простого динамического массива 
        std::cout << "\n";
    }

    std::cout << "Спасибо! Ваш динамический массив-класс: ";
    print_my_dynamic_array(my_dynamic_array); //вывести на экран значения динамического массива-класса
    std::cout << "\n";

    

    delete my_dynamic_array;

    //этот delete[] вызывает ошибку, если была применена функция увеличения размера массива
    //как правильно выделять и освобождать память здесь и в функции увеличения размера массива, чтобы не было утечек и не возникала ошибка?
    delete[] simple_int_array;
}

int get_int_value(const std::string str) //получить от пользователя число типа int
{
    std::cout << str;
    int temp_value;
    std::cin >> temp_value;
    while (std::cin.fail())
    {
      //  std::cin.clear();
      //  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      //  std::cout << str;
      //  std::cin >> temp_value;
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

void enlarge_simple_array_size_x2(int* arr, int& arr_actual_size, const int arr_logical_size) //увеличить фактический размер массива в 2 раза
{
    //организовать новый массив в 2 раза больше предыдущего
    arr_actual_size *= 2;
    int* new_arr = new int[arr_actual_size];

    //скопировать элементы из старого массива
    for (int i = 0; i < arr_logical_size; ++i)
    {
        new_arr[i] = arr[i];
    }

    //  delete[] arr;  //освободить память старого массива
      /* Поведение этого delete[] мне не ясно. Насколько я понимаю, если память была выделена ранее, ее необходимо освобождать.
      * Но есля я освобождаю память старого массива, то в новом массиве new_arr не сохраняются скопированные значения.
      *функция сейчас при закомментированном delete[] работает так, как мне нужно. Но разве тут не будет утечки памяти?
      * И если все же правильно освобождать выделенную ранее память, как это сделать, чтобы сохранялись скопированные значения элементов массива?
      *
      * И почему такая проблема не возникает в массиве, обернутом в класс Dynamic_array?
      *
      */

    arr = new_arr; //переназначить указатель
}

void append_to_dynamic_array(int* arr, const int new_value, int& arr_actual_size, int& arr_logical_size) //добавить еще один элемент к существующему массиву
{
    if (arr_actual_size == arr_logical_size) //массив полностью заполнен, запаса нет
    {
        enlarge_simple_array_size_x2(arr, arr_actual_size, arr_logical_size); //увеличить фактический размер массива в 2 раза        
    }

    arr[arr_logical_size] = new_value;
    ++arr_logical_size;
}

bool user_want_to_delete() //получить информацию от пользователя - хочет ли удалить первый элемент массива
{
    
    std::string user_reply = "";
    
    while  ((user_reply != "да") &&
            (user_reply != "нет"))
    {
        std::cout << "Удалить первый элемент? ";
        std::cin >> user_reply;
    }

    if (user_reply == "да")
        return true;

    return false;
}

void remove_dynamic_array_head(int* arr, int& arr_actual_size, int& arr_logical_size) //удалить первый элемент массива
{
    if (arr_logical_size == 0) //Невозможно удалить первый элемент, так как массив пустой
        return;

    //если логический размер массива, уменьшенный на единицу, строго больше одной трети фактического размера
    if ((arr_logical_size - 1) > (arr_actual_size / 3))
    {
        for (int i = 0; i < (arr_logical_size - 1); ++i)
        {
            arr[i] = arr[i + 1];
        }

    }
    else
    {
        //организовать новый массив в 3 раза меньше предыдущего
        int* new_arr = nullptr;
        arr_actual_size /= 3;
        new_arr = new int[arr_actual_size];

        //скопировать элементы из старого массива
        for (int i = 0; i < arr_logical_size - 1; ++i)
        {
            //новое значение не передается в simple_int_array - разобраться, почему 
            new_arr[i] = arr[i + 1];
        }

       // delete[] arr;  //освободить память старого массива
        /* Поведение этого delete[] мне не ясно. Насколько я понимаю, если память была выделена ранее, ее необходимо освобождать.
      * Но есля я освобождаю память старого массива, то в новом массиве new_arr не сохраняются скопированные значения.
      *функция сейчас при закомментированном delete[] работает так, как мне нужно. Но разве тут не будет утечки памяти?
      * И если все же правильно освобождать выделенную ранее память, как это сделать, чтобы сохранялись скопированные значения элементов массива?
      *
      * И почему такая проблема не возникает в массиве, обернутом в класс Dynamic_array?
      *
      */


        arr = new_arr; //переназначить указатель
    }

    --arr_logical_size;
}