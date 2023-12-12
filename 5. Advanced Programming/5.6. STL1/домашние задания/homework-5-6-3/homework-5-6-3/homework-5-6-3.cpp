// homework-5-6-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "my_vector.h"

int main()
{
    setlocale(LC_ALL, "rus");
    
    My_vector<int> vector1;
    vector1.print_vector();
    
    vector1.push_back(5);
    vector1.push_back(7);
    vector1.push_back(56);
    vector1.push_back(76);    
    vector1.push_back(23);
    vector1.print_vector();

    std::cout << "size of vector1 = " << vector1.size() << "\n";
    std::cout << "capacity of vector1 = " << vector1.capacity() << "\n";

    std::cout << "element [0] = " << vector1[0] << "\n";
    std::cout << "element [2] = " << vector1[2] << "\n";
    vector1[1] = 777;
    std::cout << "element [1] = " << vector1[1] << "\n";

    My_vector<int> vector2(vector1);
    vector2.print_vector();

    try
    {
        std::cout << vector2[10];
    }        
    catch (const Vector_Exception& ex)        
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    try
    {
        std::cout << vector2.at(-1);
    }
    catch (const Vector_Exception& ex)
    {
        std::cout << "Error: " << ex.what() << std::endl;
    }

    My_vector<int> vector3{3, 4, 5, 6, 7};
    vector3.push_back(8);
    vector3.print_vector();

    std::cout << "size of vector3 = " << vector3.size() << "\n";
    std::cout << "capacity of vector3 = " << vector3.capacity() << "\n";
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
