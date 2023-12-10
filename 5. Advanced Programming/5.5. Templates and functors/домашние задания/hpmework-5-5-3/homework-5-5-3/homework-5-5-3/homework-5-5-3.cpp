// homework-5-5-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "array_functor.h"

int main()
{
    int array_int[] = {10, 20, 30, 40, 60, 6};
    simple_functor<int> sf_int(array_int, 6);
    sf_int();
    std::cout << "get_sum() = " << sf_int.get_sum() << "\n";
    std::cout << "get_num() = " << sf_int.get_num() << "\n";
    std::cout << "\n";

    char array_char[] = { '1', 'd', 'r', 's' };
    simple_functor<char> sf_char(array_char, 4);
    sf_char();
    std::cout << "get_sum() = " << sf_char.get_sum() << "\n";
    std::cout << "get_num() = " << sf_char.get_num() << "\n";
    std::cout << "\n";

    double array_double[] = { 2.0, 3.4, 15, 24 };
    simple_functor<double> sf_double(array_double, 4);
    sf_double();
    std::cout << "get_sum() = " << sf_double.get_sum() << "\n";
    std::cout << "get_num() = " << sf_double.get_num() << "\n";
    std::cout << "\n";

    std::vector<int> vector_int = { 7, 5, 16, 8, 9, 3 };
    simple_functor<std::vector<int>> sf_vector_int(vector_int);
    sf_vector_int();
    std::cout << "get_sum() = " << sf_vector_int.get_sum() << "\n";
    std::cout << "get_num() = " << sf_vector_int.get_num() << "\n";
    std::cout << "\n";

    std::vector<char> vector_char = { '1', 'd', 'r', 's', 'r'};
    simple_functor<std::vector<char>> sf_vector_char(vector_char);
    sf_vector_char();
    std::cout << "get_sum() = " << sf_vector_char.get_sum() << "\n";
    std::cout << "get_num() = " << sf_vector_char.get_num() << "\n";
    std::cout << "\n";

    std::vector<double> vector_double = { 2.0, 3.4, 15, 24 };
    simple_functor<std::vector<double>> sf_vector_double(vector_double);
    sf_vector_double();
    std::cout << "get_sum() = " << sf_vector_double.get_sum() << "\n";
    std::cout << "get_num() = " << sf_vector_double.get_num() << "\n";
    std::cout << "\n";
}

