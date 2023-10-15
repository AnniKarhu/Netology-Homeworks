/*Описание
Напишите функцию print, которая принимает на вход массив произвольного размера и выводит его на экран. В программе создайте несколько массивов разного размера и используйте для вызова вашей функции.

Пример работы программы
1 2 3 4 5 6 7 8 9
6 5 4 8
1 4 3 7 5*/

#include <iostream>

void print_array(int* ptr_array, int array_size);

int main() {
    int array_1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int array_2[] = { 6, 5, 4, 8 };
    int array_3[] = { 1, 4, 3, 7, 5 };

    print_array(array_1, sizeof(array_1) / sizeof(int));
    print_array(array_2, sizeof(array_2) / sizeof(int));
    print_array(array_3, sizeof(array_3) / sizeof(int));

    return 0;
}

void print_array(int* ptr_array, int array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        std::cout << *(ptr_array + i) << "\t";
    }
    std::cout << "\n";
};