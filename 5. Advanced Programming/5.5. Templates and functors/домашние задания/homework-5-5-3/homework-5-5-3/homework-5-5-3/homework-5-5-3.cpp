// homework-5-5-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include "simple_functor.h"

int main()
{
    int array_int[6] = {10, 20, 30, 40, 60, 6};
    simple_functor<int> sf_int;    
    sf_int = std::for_each(std::begin(array_int), std::end(array_int), sf_int);
    std::cout << "\n";
    std::cout << "get_sum() = "   << sf_int.get_sum() << "\n";
    std::cout << "get_count() = " << sf_int.get_count() << "\n";
    std::cout << "\n";

    char array_char[] = { '1', 'd', 'r', 's', 'r'};
    simple_functor<char> sf_char;
    sf_char = std::for_each(std::begin(array_char), std::end(array_char), sf_char);
    std::cout << "\n";
    std::cout << "get_sum() = "   << sf_char.get_sum() << "\n";
    std::cout << "get_count() = " << sf_char.get_count() << "\n";
    std::cout << "\n";

    double array_double[] = { 2.0, 3.4, 15, 24 };
    simple_functor<double> sf_double;
    sf_double = std::for_each(std::begin(array_double), std::end(array_double), sf_double);
    std::cout << "\n";
    std::cout << "get_sum() = "   << sf_double.get_sum() << "\n";
    std::cout << "get_count() = " << sf_double.get_count() << "\n";
    std::cout << "\n";

    std::vector<int> vector_int = { 7, 5, 16, 8, 9, 3 };
    simple_functor<int> sf_vector_int;
    sf_vector_int = std::for_each(vector_int.begin(), vector_int.end(), sf_vector_int);    
    std::cout << "\n";    
    std::cout << "get_sum() = "   << sf_vector_int.get_sum() << "\n";
    std::cout << "get_count() = " << sf_vector_int.get_count() << "\n";
    std::cout << "\n";

    std::vector<char> vector_char = { '1', 'd', 'r', 's', 'r'};
    simple_functor<char> sf_vector_char;
    sf_vector_char = std::for_each(vector_char.begin(), vector_char.end(), sf_vector_char);
    std::cout << "\n";
    std::cout << "get_sum() = "   << sf_vector_char.get_sum() << "\n";
    std::cout << "get_count() = " << sf_vector_char.get_count() << "\n";
    std::cout << "\n";

    
}

