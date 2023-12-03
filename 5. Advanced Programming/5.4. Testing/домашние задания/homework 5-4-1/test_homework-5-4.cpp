// homework 5-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include "DoubleLinkedList.h"

TEST_CASE("test Class List", "[test_class_list]") 
{  
    SECTION("Section test List.Empty()")
    {
        List my_new_list;        
        CHECK(my_new_list.Empty() == true);    
        
        my_new_list.PushFront(1);
        CHECK(my_new_list.Empty() == false);        
        my_new_list.Clear();
        CHECK(my_new_list.Empty() == true);
    }

    SECTION("Section test List.Size()")
    {
        List my_new_list;
        REQUIRE(my_new_list.Size() == 0);
        my_new_list.PushFront(1);
        CHECK(my_new_list.Size() == 1);
        my_new_list.PushBack(1);
        CHECK(my_new_list.Size() == 2);
        my_new_list.Clear();
        CHECK(my_new_list.Size() == 0);
        for (int i = 0; i < 10; ++i)
        {
            my_new_list.PushFront(i);
        }
        CHECK(my_new_list.Size() == 10);

        for (int i = 20; i > 10; --i)
        {
            my_new_list.PushBack(i);
        }
        CHECK(my_new_list.Size() == 20);

        for (int i = 0; i < 3; ++i)
        {
            try
            {
                my_new_list.PopBack();
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
        CHECK(my_new_list.Size() == 17);

        for (int i = 0; i < 5; ++i)
        {
            try
            {
                my_new_list.PopFront();
            }
            catch (std::exception const& ex)
            {
               // std::cout << ex.what() << "\n";
            }
            catch (...)
            {
               // std::cout << "unknown error, can't pop a value\n";
            }
        }
        CHECK(my_new_list.Size() == 12);

        for (int i = 0; i < 20; ++i)
        {
            try
            {
                my_new_list.PopFront();
            }
            catch (std::exception const& ex)
            {
               // std::cout << ex.what() << "\n";
            }
            catch (...)
            {
               // std::cout << "unknown error, can't pop a value\n";
            }
        }
        CHECK(my_new_list.Size() == 0);
    }
}

int main()
{
    return Catch::Session().run();
}


