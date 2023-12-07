// homework-5-5-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

#include "func_square.h"


int main()
{
    std::cout << "int example: \n";
    int val1 = 4;
    std::cout << "[IN]:\t" << val1 << "\n";
    std::cout << "[OUT]:\t" << func_square(val1) << "\n\n";

    std::cout << "double example: \n";
    double val2 = 10.0;
    std::cout << "[IN]:\t" << val2 << "\n";
    std::cout << "[OUT]:\t" << func_square(val2) << "\n\n";
    
    std::cout << "vector <int> example: \n";
    std::vector<int> vec_int{ -1, 4, 8 };
    std::cout << "[IN]:\t";
    for (auto it : vec_int)
    {
        std::cout << it << "\t";
    }
    std::cout <<  "\n";

    vec_int = func_square(vec_int);
    std::cout << "[OUT]:\t";
    for (auto it : vec_int)
    {
        std::cout << it << "\t";
    }
    std::cout << "\n\n";

    std::cout << "vector <char> example: \n";
    std::vector<int> vec_char{ 'a', '4', 'b' };
    std::cout << "[IN]:\t";
    for (auto it : vec_char)
    {
        std::cout << it << "\t";
    }
    std::cout << "\n";

    vec_char = func_square(vec_char);
    std::cout << "[OUT]:\t";
    for (auto it : vec_char)
    {
        std::cout << it << "\t";
    }
    std::cout << "\n";
}

