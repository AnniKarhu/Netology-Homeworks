// homework 5-3-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <string>

#include "smart_array.h"
#include "array_exception.h"


int main()
{
    Smart_array arr(5);
    arr.add_element(1);
    arr.add_element(4);
    arr.add_element(155);
    arr.print_array();

    Smart_array arr3(arr);
    arr3.print_array();

    Smart_array new_array(2);
    new_array.add_element(44);
    new_array.add_element(34);
    new_array.print_array();

    arr = new_array;
    arr.print_array();

    const Smart_array object(5);
    new_array = object;
    new_array.print_array();

  
}