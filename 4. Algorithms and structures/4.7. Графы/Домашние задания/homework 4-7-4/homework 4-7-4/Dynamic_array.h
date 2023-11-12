#pragma once

#include <iostream>

class Dynamic_array
{
private:
    int* arr = nullptr;
    int logical_size = 0;
    int actual_size = 0;
    void enlarge_array_size_x2(); //увеличить фактический размер массива
    
public:
    explicit Dynamic_array(unsigned int new_logical_size, unsigned int new_actual_size);
    ~Dynamic_array();
  //  bool set_actual_size(const int new_size);
  //  bool set_logical_size(const int new_size);
    int get_actual_size();
    int get_logical_size();
    int operator[](const int elem_index);
    bool add_array_element(const int elem_index, const int new_value); //ввести значение элемента в логической части массива
    int get_array_element(const int elem_index, bool& get_result);
    void append_to_dynamic_array(const int new_value); //добавить еще один элемент к существующему массиву
};