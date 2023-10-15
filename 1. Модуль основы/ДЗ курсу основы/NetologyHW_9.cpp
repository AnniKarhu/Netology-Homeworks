
//

#include <iostream>

int main()
{
   
	//Задание 9.3
#include <iostream>

    void reverse(int* ptr_array, int array_size);
    void print_array(int* ptr_array, int array_size);

    int main() {
        int size;
        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };


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
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
