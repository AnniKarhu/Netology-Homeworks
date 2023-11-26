#pragma once

class Smart_array
{
private:
    int* arr = nullptr;
    int array_size = 0;
    int add_to_array_index = 0;

public:
    explicit Smart_array(const int new_size);
    ~Smart_array();
    
    void add_element(const int new_value); //добавить элемент
    int get_element(const int elem_index);   //получить элемент по индексу
    void print_array(); //вывести на экран

    Smart_array& operator=(Smart_array &arr2);
};