#pragma once

#include "vector_exception.h"
#include <initializer_list>

template <class T>
class My_vector
{
protected:
    T* arr;
    int array_size = 1;  //фактический размер массива
    int add_to_array_index = 0; //указатель на индекс для добавленя следующего элемента
    void enlarge_array_size_x2() //увеличить фактический размер массива
    {
        //организовать новый массив в 2 раза больше предыдущего
        T* new_arr = nullptr;
        array_size *= 2;
        new_arr = new T[array_size]();

        //скопировать элементы из старого массива
        for (int i = 0; i <= add_to_array_index; ++i)
        {
            new_arr[i] = arr[i];
        }

        delete[] arr;  //освободить память старого массива
        arr = new_arr; //переназначить указатель
    }

public:
    My_vector(std::initializer_list<T> input_list)
    {
        array_size = input_list.size();
        add_to_array_index = array_size;
        arr = new T[array_size](); 
        int arr_index = 0;
       // std::cout << "Input list = ";
        for (auto elem : input_list)
        {
           // std::cout << elem << "\t";
            arr[arr_index] = elem;
            ++arr_index;
        }
       // std::cout << "\n";
    }

    My_vector()
    {
        arr = new T[array_size]();
    }

    ~My_vector()
    {
        delete[] arr;
    }

    My_vector(const My_vector& My_vector2)
    {
        array_size = My_vector2.array_size;
        arr = new T[array_size];
        add_to_array_index = My_vector2.add_to_array_index;
        for (int i = 0; i < array_size; ++i)
        {
            arr[i] = My_vector2.arr[i];
        }
    }


    My_vector& operator=(const My_vector& My_vector2)
    {
        if (this != &My_vector2)
        {
            delete[] arr;
            array_size = My_vector2.array_size;
            add_to_array_index = My_vector2.add_to_array_index;
            arr = new T[array_size];

            for (int i = 0; i < array_size; ++i)
            {
                arr[i] = My_vector2.arr[i];
            }
        }
        return *this;
    }
   
    void push_back(T value)
    {
        if (arr == nullptr) //по какой-то причине память не выделена
        {
            throw Vector_Exception(); //выбросить ошибку
        }

        if (array_size == add_to_array_index) //массив полностью заполнен, запаса нет
        {
            enlarge_array_size_x2(); //увеличить фактический массив в 2 раза
        }

        arr[add_to_array_index] = value;
        ++add_to_array_index;
        
    }
   
    T at (int index)   //получить элемент по индексу
    {
        if ((index < 0) ||
            (index >= add_to_array_index) || 
            (arr == nullptr))
        {
            throw Vector_Exception(); //выбросить ошибку
        }

        return arr[index];
    }

    T& operator[](int index)
    {
        if ((index < 0) ||
            (index >= add_to_array_index) ||
            (arr == nullptr))
        {
            throw Vector_Exception(); //выбросить ошибку
        }

        return arr[index];
    }

    int size() //количество элементов в контейнере;
    {
        return add_to_array_index;
    }

    int capacity() // количество элементов, которое может вместить контейнер до нового выделения памяти
    {
        return array_size;
    }

    void print_vector()
    {
        for (int i = 0; i < add_to_array_index; ++i)
        {
            std::cout << arr[i] << "\t";
        }

        for (int i = add_to_array_index; i < array_size; ++i)
        {
            std::cout << "_" << "\t";
        }
        std::cout << "\n";
    }

};