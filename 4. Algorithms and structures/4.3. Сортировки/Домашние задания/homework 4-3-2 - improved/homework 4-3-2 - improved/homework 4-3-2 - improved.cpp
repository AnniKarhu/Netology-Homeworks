// homework 4-3-2 - improved.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <algorithm>



int pivoting(int* arr, int left, int right);
void quick_sort(int* arr, int left, int right);
void swap(int& A, int& B);
void print_array(int* array, int size, std::string temp_str); //вывести массив на экран

int main()
{
    setlocale(LC_ALL, "rus");

    const int size_1 = 10;
    int test_array_1[size_1] = { 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };

    print_array(test_array_1, size_1, "Исходный массив: ");
    quick_sort(test_array_1, 0, size_1 - 1);
    print_array(test_array_1, size_1, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_2 = 15;
    int test_array_2[size_2] = { 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74 };
    print_array(test_array_2, size_2, "Исходный массив: ");
    quick_sort(test_array_2, 0, size_2 - 1);
    print_array(test_array_2, size_2, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_3 = 18;
    int test_array_3[size_3] = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };
    print_array(test_array_3, size_3, "Исходный массив: ");
    quick_sort(test_array_3, 0, size_3 - 1);
    print_array(test_array_3, size_3, "Отсортированный массив: ");
    std::cout << "\n";

    return 0;
}

int pivoting(int* arr, int left, int right)
{
    // Пивот -  крайний правый элемент  массива
    int pivot = arr[right];

    // элементы массива меньше пивота перекидываются влево от индекса temp
    // элементы массива больше пивота перекидываются вправо от индекса temp
    int temp = left;

    // если элемент массива < = pivot, индекс temp увеличивается, и  элемент меняется местами с пивотом
    for (int i = left; i < right; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(arr[i], arr[temp]);
            temp++;
        }
    }

    // поменять местами  с пивотом
    swap(arr[temp], arr[right]);

    // вернуть номер нового пивота
    return temp;
}

// Процедура быстрой сортировки
void quick_sort(int* arr, int left, int right)
{    
    if (left >= right) 
    {
        return;
    }

    // переставить элементы
    int pivot = pivoting(arr, left, right);

    // сортировать подмассив слева от пивота
    quick_sort(arr, left, pivot - 1);

    // сортировать подмассив справа от пивота
    quick_sort(arr, pivot + 1, right);
}

void swap(int& A, int& B)
{
    int temp = A;
    A = B;
    B = temp;
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
