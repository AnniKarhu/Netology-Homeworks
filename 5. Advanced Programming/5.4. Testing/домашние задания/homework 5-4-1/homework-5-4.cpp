// homework 5-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "DoubleLinkedList.h"

int main()
{
    List my_new_list;
    if (my_new_list.Empty())
    {
        std::cout << "The list is empty\n";
    }
    else
    {
        std::cout << "The list isn't empty\n";
    }

    std::cout << "Size of the list = " << my_new_list.Size() << std::endl;
    

    for (int i = 0; i < 10; ++i)
    {
        my_new_list.PushFront(i);
    }

    for (int i = 20; i > 0; --i)
    {
        my_new_list.PushBack(i);
    }

    if (my_new_list.Empty())
    {
        std::cout << "The list is empty\n";
    }
    else
    {
        std::cout << "The list isn't empty\n";
    }

    std::cout << "Size of the list = " << my_new_list.Size() << std::endl;

    try
    {
        int value = my_new_list.PopBack();
        std::cout << "PopBack value = " << value << "\n";

        value = my_new_list.PopFront();
        std::cout << "PopFront value = " << value << "\n";
    }
    catch (std::exception const& ex)
    {
        std::cout << ex.what() << "\n";
    }
    catch (...)
    {
        std::cout << "unknown error, can't pop a value\n";
    }
    
}


