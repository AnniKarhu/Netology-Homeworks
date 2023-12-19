// homework-5-8-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

#include "my_unique_ptr.h"
#include "test_class.h"

int main()
{
    //std::vector<int> int_vector = { 1, 2, 3, 4, 5 };
    std::initializer_list<int> init_list = { 1, 2, 3, 4, 5 };
    my_unique_ptr<std::vector<int>> new_ptr(new std::vector<int>(init_list));

}

