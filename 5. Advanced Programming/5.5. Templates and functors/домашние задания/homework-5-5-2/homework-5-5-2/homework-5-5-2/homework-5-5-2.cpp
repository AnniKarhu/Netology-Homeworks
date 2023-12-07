// homework-5-5-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "table.h"

int main()
{
    
    setlocale(LC_ALL, "Russian");

    table<int> new_table(2, 3);
    // table<int> new_table2 = new_table; //присваивание запрещено
    // table<int> new_table2(new_table); //конструктор копирования запрещен

    std::cout << new_table.getElement(1, 1) << "\n";
    new_table.setElement(1, 1, 10);
    std::cout << new_table.getElement(1, 1) << "\n";

    std::cout << new_table[1][1] << "\n";

    new_table[0][1] = 20;
    std::cout << new_table[0][1] << "\n";

    std::cout << new_table.size() << "\n";

    try
    {
        std::cout << new_table[1][-1] << "\n"; //не выкинет ошибку
        std::cout << new_table[2][1] << "\n"; //выкинет ошибку
        std::cout << new_table[-2][1] << "\n"; //выкинет ошибку
    }
    catch (const std::exception& ex)
    {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    catch (...)
    {

    }

    auto test = table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << "\n";; // выводит 4
     
   
    const  table<int> test_table(2, 3);
    int test_val = test_table[1][1];
    std::cout << test_val;  


}

