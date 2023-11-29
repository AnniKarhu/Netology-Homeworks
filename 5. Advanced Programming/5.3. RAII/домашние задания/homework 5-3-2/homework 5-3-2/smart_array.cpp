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

Smart_array::Smart_array(const Smart_array& arr2)
{
    array_size = arr2.array_size;
    arr = new int[array_size];

    if (array_size > 0)
    {
        for (int i = 0; i < array_size; ++i)
        {
            arr[i] = arr2.arr[i];
        }
    }
}

Smart_array::~Smart_array()
{
    delete[] arr;    
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

Smart_array& Smart_array::operator=(const Smart_array &arr2)
{
    delete[] arr;
    this->array_size = arr2.array_size;
    arr = new int[array_size];
    
    if (array_size > 0)
    {
        for (int i = 0; i < array_size; ++i)
        {
            arr[i] = arr2.arr[i];
        }
    }

    return *this;
}

void Smart_array::print_array()
{
    for (int i = 0; i < array_size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}
