// homework 4-3-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

void merge_sort(int* arr, int size);
void merge(int* array_A, const int size_A, int* array_B, const int size_B, int* array_C);
void print_array(int* array, int size, std::string temp_str); //вывести массив на экран

int main()
{
    setlocale(LC_ALL, "rus");

      
    const int size_1 =  10;
    int test_array_1[size_1] = { 3, 43, 38, 29,  18, 72, 57, 61, 2, 33 };

    print_array(test_array_1, size_1, "Исходный массив: ");
    merge_sort(test_array_1, size_1);
    print_array(test_array_1, size_1, "Отсортированный массив: ");
    std::cout << "\n";

    const int size_2 = 15;
    int test_array_2[size_2] = { 88, 91, 87, 59, 53, 49, 29, 16, 4, 27, 28, 89, 2, 25, 74 };
    print_array(test_array_2, size_2, "Исходный массив: ");
    merge_sort(test_array_2, size_2);
    print_array(test_array_2, size_2, "Отсортированный массив: ");
    std::cout << "\n";
    
    const int size_3 = 18;
    int test_array_3[size_3] = { 24, 66, 20, 79, 30, 16, 19, 62, 94, 59, 0, 7, 59, 90, 84, 60, 95, 62 };
    print_array(test_array_3, size_3, "Исходный массив: ");
    merge_sort(test_array_3, size_3);
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

void merge_sort(int* arr, int size)
{
   if (size == 1)
   {
       return;
   }

   int right_index = size / 2; //размер первой половины массива равен стартовому индексу правой половины массива   
   merge_sort(arr, right_index); //отсортировать левую половину - размер массива равен половине входного массива с отбрасыванием остатка
   
   int right_size = right_index + size % 2; //размер правой половины равен размеру левой половины + остаток от деления
   merge_sort(&arr[right_index], right_size); //отсортировать правую половину - размер массива right_size

   merge(arr, right_index, &arr[right_index], right_size, arr);
}

void merge(int* array_A, const int size_A, int* array_B, const int size_B, int* array_C)
{
    int index_A = 0;
    int index_B = 0;
    int index_C = 0; 

    int* temp_array = new int[size_A + size_B]{};

    while ((index_A < size_A) || (index_B < size_B)) // пока не закончатся оба массива
    {
        if (index_A == size_A) // массив А закончился
        {
            temp_array[index_C] = array_B[index_B]; //переложить в массив С оставшиеся элементы из В
            ++index_B;
        }
        else 
        if (index_B == size_B) // массив B закончился
        {
            temp_array[index_C] = array_A[index_A]; //переложить в массив С оставшиеся элементы из A
            ++index_A;
        }
        else  //еще есть данные в обоих массивах
        if (array_A[index_A] <= array_B[index_B]) //значение в массиве А меньше - берем его
        {
            temp_array[index_C] = array_A[index_A];
            ++index_A;
        }
        else //значение в массиве B меньше - берем его
        {
            temp_array[index_C] = array_B[index_B];
            ++index_B;
        }

        ++index_C;
    }
    for (int i = 0; i < size_A + size_B; ++i)
    {
        array_C[i] = temp_array[i];
    }

    delete[] temp_array;
}