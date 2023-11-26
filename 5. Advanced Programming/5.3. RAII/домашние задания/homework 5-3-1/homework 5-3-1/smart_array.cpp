#include "smart_array.h"
#include "array_exception.h"

Smart_array::Smart_array(const int new_size)
{
    if (new_size > 0)
    {
        arr = new int[new_size]();
        array_size = new_size;
    }  
}

Smart_array::~Smart_array()
{
    if (arr != nullptr)
    {
        delete[] arr;
    }
}

void Smart_array::add_element(const int new_value)
{
    if ((add_to_array_index >= array_size) ||
        (arr == nullptr))
    {
        throw Array_Exception(); //выбросить ошибку
    }
        

    arr[add_to_array_index] = new_value;
    ++add_to_array_index;
 }

int Smart_array::get_element(const int elem_index)
{
    if ((elem_index < 0) ||
        (elem_index >= array_size) ||
        (arr == nullptr))
    {
        throw Array_Exception(); //выбросить ошибку
    }

    return arr[elem_index];
}
