// homework-5-5-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "table.h"
//#include "cols_env.h"

int main()
{

    setlocale(LC_ALL, "Russian");

    table<int> new_table(2, 3);
    std::cout << "new_table.size = " << new_table.size() << "\n";

    try
    {
        std::cout << new_table.getElement(1, 1) << "\n";
        new_table.setElement(1, 1, 10);
        new_table.setElement(0, 0, 20);
        std::cout << "getElement(1, 1) = " << new_table.getElement(1, 1) << "\n";
        std::cout << "getElement(0, 0) = " << new_table.getElement(0, 0) << "\n";

        new_table[0][1] = 30;
        std::cout << "[0][1] = " << new_table[0][1] << "\n";


        // std::cout << new_table.getElement(10, 1) << "\n"; //выбросит исключение
        // std::cout << new_table.getElement(1, 10) << "\n"; //выбросит исключение

         //new_table[0][10] = 30;                                   //выбросит исключение
         //std::cout << "[0][10] = " << new_table[0][10] << "\n"; //выбросит исключение
    }
    catch (const std::exception& ex)
    {
        std::cout << "Ошибка: " << ex.what() << std::endl;
    }
    catch (...)
    {

    }

    std::cout << "\n";

    table<int> table2(new_table);
    std::cout << "table2.getElement(1, 1) = " << table2.getElement(1, 1) << "\n";
    std::cout << "table2.getElement(0, 0) = " << table2.getElement(0, 0) << "\n";
    std::cout << "table2[0][1] = " << table2[0][1] << "\n";


    std::cout << "\n";
    auto table3 = table2;
    std::cout << "table3.getElement(1, 1) = " << table3.getElement(1, 1) << "\n";
    std::cout << "table3.getElement(0, 0) = " << table3.getElement(0, 0) << "\n";
    std::cout << "table3[0][1] = " << table3[0][1] << "\n";

}
