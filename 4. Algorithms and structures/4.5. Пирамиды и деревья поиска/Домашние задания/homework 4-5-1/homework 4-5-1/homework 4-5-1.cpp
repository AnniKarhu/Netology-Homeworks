// homework 4-5-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>

void print_pyramid(int* arr, int size); //вывод пирамиды на консоль

int main()
{
    setlocale(LC_ALL, "rus");

    const int size_1 = 6;
    int test_array_1[size_1] = { 1, 3, 6, 5, 9, 8 };
    print_pyramid(test_array_1, size_1); //вывод пирамиды на консоль
    std::cout << "\n\n";

    const int size_2 = 8;
    int test_array_2[size_2] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    print_pyramid(test_array_2, size_2); //вывод пирамиды на консоль
    std::cout << "\n\n";

    const int size_3 = 10;
    int test_array_3[size_3] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4 };
    print_pyramid(test_array_3, size_3); //вывод пирамиды на консоль
    std::cout << "\n\n";
   
}

void print_pyramid(int* arr, int size) //вывод пирамиды на консоль
{
    std::cout << "Исходный массив: ";
    for (int i = 0; i < size; ++i)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << "\nПирамида:\n";

    //корень пирамиды - нулевой элемент массива
    int level = 0;
    std::string role_str = "root";
    int parent_index = 0;
    int index = 0; 
    int max_level_index = 0; //максимальный индекс на уровне. 0-й уровень - один элемент с индексом 0

    std::cout << level << " " << role_str <<  arr[index] << "\n";
    while (index < size-1) //вывести информацию по всем элементам массива
    {      
        ++index;

        //определить уровень элемента по его индексу
        if (index > max_level_index) //если текущий индекс больше максимального индекса для текущего уровня
        {
            ++level; //увеличить номер уровня
            max_level_index += pow(2, level); //максимальный индекс на новом уровне = макс. индекс на предыдущем уровне + 2 в степени уровень
        }

        int temp_div = index % 2; //temp_div определяет, четный или нечетный индекс  
        switch (temp_div)
        {
        case 0:
            role_str = "right";//четные индексы - right
            parent_index = (index - 2) / 2; //индекс родителя
            break;

        case 1:
            role_str = "left";//нечетные индексы - left   
            parent_index = (index - 1) / 2; //индекс родителя
            break;
        }
        std::cout << level << " " << role_str << "(" << arr[parent_index] << ") " << arr[index] << "\n";
    }
    

}