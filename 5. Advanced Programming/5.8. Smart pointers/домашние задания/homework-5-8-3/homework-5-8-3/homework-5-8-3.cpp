// homework-5-8-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>

#include "my_unique_ptr.h"


int main()
{
       
    //указатель на первый вектор
    std::initializer_list<int> init_list_1 = { 1, 2, 3, 4, 5 };
    my_unique_ptr<std::vector<int>> new_ptr_1(new std::vector<int>(init_list_1));

    //обращение к полям первого вектора по указателю new_ptr_1
    std::cout << "size of vector_1 = " << new_ptr_1->size() << "\n";
    std::cout << "begin of vector_1 = " << *(new_ptr_1->begin()) << "\n";
    *(new_ptr_1->end() - 1) = 10;
    std::cout << "end of vector_1 = " << *(new_ptr_1->end()-1) << "\n";
    std::cout << "\n";

    std::vector<int>* get_vector; 

    {
        //указатель на второй вектор
        std::initializer_list<int> init_list_2 = { 6, 7, 8, 9, 10, 11, 12 };
        my_unique_ptr<std::vector<int>> new_ptr_2(new std::vector<int>(init_list_2));

        //обращение к полям второго вектора по указателю new_ptr_2
        std::cout << "size of vector_2 = " << new_ptr_2->size() << "\n";
        std::cout << "begin of vector_2 = " << *(new_ptr_2->begin()) << "\n";
        *(new_ptr_2->end() - 1) = 10;
        std::cout << "end of vector_2 = " << *(new_ptr_2->end() - 1) << "\n";
        std::cout << "\n";

        //new_ptr_1 = new_ptr_2;  //операция присваивания запрещена
        //auto new_ptr3(new_ptr_2); //конструктор копирования запрещен

        
        get_vector = new_ptr_2.release();//передача указателю get_vector
    }

    //new_ptr_2 удален    
    //*(new_ptr_2->end() - 1) = 10;
   
    //обращение к полям  вектора get_vector
    std::cout << "size of get_vector = " << get_vector->size() << "\n";
    std::cout << "begin of get_vector = " << *(get_vector->begin()) << "\n";
    *(get_vector->end() - 1) = 10;
    std::cout << "end of get_vector = " << *(get_vector->end() - 1) << "\n";
    std::cout << "\n";



}

