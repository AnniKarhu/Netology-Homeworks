// homework 4-3-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
void print_array(int* array, int size, std::string temp_str); //вывести массив на экран
void count_sort(int* arr, int size); //сортировка подсчетом

int main()
{
    setlocale(LC_ALL, "rus");

    const int size_1 = 30;
    int test_array_1[size_1] = { 19, 14, 22, 22, 17, 22, 13, 21, 20, 24, 18, 10, 17, 16, 17, 20, 22, 11, 20, 16, 14, 13, 10, 22, 18, 14, 16, 24, 19, 17 };
    print_array(test_array_1, size_1, "Исходный массив: ");
    count_sort(test_array_1, size_1);
    print_array(test_array_1, size_1, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_2 = 40;
    int test_array_2[size_2] = { 16, 17, 14, 20, 22, 20, 17, 22, 16, 19, 23, 24, 20, 22, 21, 18, 14, 16, 17, 21, 10, 11, 19, 23, 11, 11, 17, 17, 11, 21, 17, 11, 17, 16, 12, 11, 16, 22, 23, 16 };
    print_array(test_array_2, size_2, "Исходный массив: ");
    count_sort(test_array_2, size_2);
    print_array(test_array_2, size_2, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_3 = 45;
    int test_array_3[size_3] = { 21, 15, 19, 18, 23, 12, 18, 18, 19, 23, 12, 20, 15, 22, 21, 18, 19, 20, 12, 16, 20, 14, 17, 13, 10, 23, 19, 14, 10, 22, 19, 12, 24, 23, 22, 15, 13, 22, 18, 18, 11, 23, 24, 17, 10 };
    print_array(test_array_3, size_3, "Исходный массив: ");
    count_sort(test_array_3, size_3);
    print_array(test_array_3, size_3, "Отсортированный массив: ");
    std::cout << "\n";
}

void print_array(int* array, int size, std::string temp_str) //вывести массив на экран
{
    std::cout << temp_str;
    for (int i = 0; i < size; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

void count_sort(int* arr, int size) //сортировка подсчетом
{
    int min_value = 10;
    int max_value = 24;
    int temp_array_size = max_value - min_value + 1; //размер вспомогательного массива равен возможному количеству уникальных значений в исходном массиве
    int* temp_array = new int[temp_array_size] {}; 

    int t_index;
    for (int i = 0; i < size; ++i)
    {
        t_index = arr[i] - min_value; //число сортируемого массива минус минимальное значение - это индекс вспомогательного массива
        ++temp_array[t_index]; //значение элемента вспомогательного массива увеличивается на 1 для каждого попадания
    }

    t_index = 0; //счетчик - индекс для заполнения основного массива
    for (int i = 0; i < temp_array_size; ++i)
    {
        for (int j = temp_array[i]; j > 0; j--) 
        {
            arr[t_index] = i + min_value;
            ++t_index;
        }
    }

    delete[] temp_array;
}