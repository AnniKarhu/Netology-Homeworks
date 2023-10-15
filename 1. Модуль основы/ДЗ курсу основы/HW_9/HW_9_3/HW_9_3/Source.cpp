/*Описание
Напишите функцию reverse, которая принимает на вход массив произвольного размера и «разворачивает» его в обратную сторону — то есть первый элемент становится последним и наоборот. Выведите на консоль массив до вызова функции и после вызова функции.

Обратите внимание, что функция reverse должна изменять передаваемый ей массив. Элементы в нём должны изменить свой порядок.

Пример работы программы
До функции reverse: 1 2 3 4 5 6 7 8 9
После функции reverse: 9 8 7 6 5 4 3 2 1
*/

#include <iostream>

void reverse(int* ptr_array, int array_size);
void reverse2(int* ptr_array, int array_size);
void print_array(int* ptr_array, int array_size);

int main() {
    int size;
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 20 };


    size = sizeof(array) / sizeof(int);
    print_array(array, size);
    reverse(array, size);
    print_array(array, size);
    reverse2(array, size);
    print_array(array, size);

    return 0;
}

void reverse(int* array_ptr, int array_size)
{
    for (int i = 0; i < array_size / 2; ++i)
    {
        int temp;
        int* ptr_a;
        int* ptr_b;
        ptr_a = array_ptr + i;
        ptr_b = array_ptr + array_size - 1 - i;

        temp = *ptr_b;
        *ptr_b = *ptr_a;
        *ptr_a = temp;

    }
}

void reverse2(int arr1[], int size)
{
    for (int i = size-1; i >size / 2; i--)
    {
        int temp;
        int* a;
        int* b;
        a = arr1 + i;
        b = arr1 + size - 1 - i;

        temp = *ptr_b;
        *ptr_b = *ptr_a;
        *ptr_a = temp;

    }
}

void print_array(int* ptr_array, int array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        std::cout << *(ptr_array + i) << "\t";
    }
    std::cout << "\n";
};