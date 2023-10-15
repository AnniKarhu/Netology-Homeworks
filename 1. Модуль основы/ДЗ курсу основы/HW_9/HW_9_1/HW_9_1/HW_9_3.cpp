#include <iostream>

void reverse(int* ptr_array, int array_size);
void print_array(int* ptr_array, int array_size);

int main() {
    int size;
    int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 20 };


    size = sizeof(array) / sizeof(int);
    print_array(array, size);
    reverse(array, size);
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

void print_array(int* ptr_array, int array_size)
{
    for (int i = 0; i < array_size; ++i)
    {
        std::cout << *(ptr_array + i) << "\t";
    }
    std::cout << "\n";
};