// homework 4-3-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
void swap(int* A, int* B); //поменять местами
int pivoting(int* arr, int size, int pi); //пивотирование
void quick_sort(int* arr, int size); //быстрая сортировка
void print_array(int* array, int size, std::string temp_str); //вывести массив на экран


int main()
{
    setlocale(LC_ALL, "rus");
    
    const int size_1 =  10;
    int test_array_1[size_1] = { 3, 43, 38, 29, 18, 72, 57, 61, 2, 33 };

    print_array(test_array_1, size_1, "Исходный массив: ");
    quick_sort(test_array_1, size_1);
    print_array(test_array_1, size_1, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_2 = 15;
    int test_array_2[size_2] = { 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74 };
    print_array(test_array_2, size_2, "Исходный массив: ");
    quick_sort(test_array_2, size_2);
    print_array(test_array_2, size_2, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_3 = 18;
    int test_array_3[size_3] = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };
    print_array(test_array_3, size_3, "Исходный массив: ");
    quick_sort(test_array_3, size_3);
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

void quick_sort(int* arr, int size)
{
    if (size == 1)
    {
        return;
    }
    int pi = size / 2;
    int border = pivoting(arr, size, pi);
    quick_sort(arr, border);

    int arr_size = size - border;
    quick_sort(&arr[border], arr_size);

}

int pivoting(int* arr, int size, int pi)
{
    int left = 0;
    int right = size - 1;
    int pivot = arr[pi];
    while (1)
    {
        while (arr[left] < pivot)
        {
            ++left;
        }

        while (arr[right] > pivot)
        {
            --right;
        }

        if (left >= right)
        {
            return left;
        }

        swap(&arr[left], &arr[right]);
        ++left;
        --right;
    }

}

void swap(int* A, int* B) //поменять местами
{
    int temp = *A;
    *A = *B;
    *B = temp;
}