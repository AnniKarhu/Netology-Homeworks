#pragma once

#include <iostream>

class Dynamic_array
{
private:
    int* arr = nullptr;
    int logical_size = 0;
    int actual_size = 0;
    
    
public:
    Dynamic_array();
    ~Dynamic_array();
    bool set_actual_size(const int new_size);
    bool set_logical_size(const int new_size);
    int get_actual_size();
    int get_logical_size();
    //  int operator[](const int elem_index);
    bool add_array_element(const int elem_index, const int new_value); 
    int get_array_element(const int elem_index, bool& get_result);
};