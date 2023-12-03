// homework 5-4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include "DoubleLinkedList.h"

TEST_CASE("test Class List", "[test_class_list]") 
{      
    SECTION("Section test List.PushFront()")
    {
        List my_new_list;
        my_new_list.PushFront(1);
        CHECK(my_new_list.Size() == 1);        
        my_new_list.PushFront(1);
        CHECK(my_new_list.Size() == 2);

        for (int i = 0; i < 10; ++i)
        {
            my_new_list.PushFront(i);
        }

        CHECK(my_new_list.Size() == 12);
    }

    SECTION("Section test List.PushBack()")
    {
        List my_new_list;
        my_new_list.PushBack(1);
        CHECK(my_new_list.Size() == 1);
        my_new_list.PushBack(1);
        CHECK(my_new_list.Size() == 2);

        for (int i = 0; i < 10; ++i)
        {
            my_new_list.PushFront(i);
        }

        CHECK(my_new_list.Size() == 12);
    }

    SECTION("Section test List.PopFront() &  List.PopBack()")
    {   
        List my_new_list;
        int test_bool1 = false;
        int test_bool2 = false;
        try
        {
            my_new_list.PopFront();
            test_bool1 = true;
        }
        catch (std::exception const& ex)
        {
            // std::cout << ex.what() << "\n";
            test_bool2 = true;
        }
        catch (...)
        {
            // std::cout << "unknown error, can't pop a value\n";
            test_bool2 = true;
        }
        CHECK(test_bool1 == false);
        CHECK(test_bool2 == true);

        test_bool1 = false;
        test_bool2 = false;
        try
        {
            my_new_list.PopBack();
            test_bool1 = true;
        }
        catch (std::exception const& ex)
        {
            // std::cout << ex.what() << "\n";
            test_bool2 = true;
        }
        catch (...)
        {
            // std::cout << "unknown error, can't pop a value\n";
            test_bool2 = true;
        }
        CHECK(test_bool1 == false);
        CHECK(test_bool2 == true);

        my_new_list.PushFront(1);
        CHECK(my_new_list.Size() == 1);

        my_new_list.PushBack(10);
        CHECK(my_new_list.Size() == 2);

        int test_value = my_new_list.PopBack();
        CHECK(test_value == 10);

        test_value = my_new_list.PopBack();
        CHECK(test_value == 1);

        my_new_list.PushBack(10);
        CHECK(my_new_list.Size() == 1);

        my_new_list.PushFront(20);
        CHECK(my_new_list.Size() == 2);

        my_new_list.PushBack(30);
        CHECK(my_new_list.Size() == 3);

        test_value = my_new_list.PopFront();
        CHECK(test_value == 20);
        test_value = my_new_list.PopFront();
        CHECK(test_value == 10);
        test_value = my_new_list.PopFront();
        CHECK(test_value == 30);        

        for (int i = 9; i >=0; --i)
        {
            my_new_list.PushFront(i);
        }

        for (int i = 10; i < 20; ++i)
        {
            my_new_list.PushBack(i);
        }

        for (int i = 0; i < 15; ++i)
        {
            test_value = my_new_list.PopFront();           
            CHECK(test_value == i);
        }

        for (int i = 19; i > 14; --i)
        {
            test_value = my_new_list.PopBack();
            CHECK(test_value == i);
        }        
    }
}

int main()
{
    return Catch::Session().run();
}


