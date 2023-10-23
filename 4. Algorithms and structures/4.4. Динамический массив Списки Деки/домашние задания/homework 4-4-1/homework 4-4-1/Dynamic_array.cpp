#include "Dynamic_array.h"

Dynamic_array::Dynamic_array()
{

}

Dynamic_array::~Dynamic_array()
{
    if (arr != nullptr)
    {
        delete[] arr;
    }
    
}

bool Dynamic_array::set_actual_size(const int new_size)
{    
    if ((new_size <= 0) ||          //попытка задать некорректный размер массива
        (actual_size != 0) ||       //размер массива уже был задан
        (new_size < logical_size))  //фактический размер массива нельз€ задавать меньше, чем логический размер
    {
        std::cout << "Ќедопустимые размер фактического массива \n";
        return false;
    }

    actual_size = new_size;
    arr = new int[new_size];
    return true;  
   
}

bool Dynamic_array::set_logical_size(const int new_size)
{
    if (new_size < 0)
    {
        std::cout << "ќшибка! Ћогический размер массива не может быть меньше 0!\n";
        return false;
    }

    
    if (new_size <= actual_size)
    {
        logical_size = new_size;
        return true;
    }
    else
    {
        std::cout << "ќшибка! Ћогический размер массива не может превышать фактический!\n";
        return false;
    }
}

int Dynamic_array::get_actual_size()
{
    return actual_size;
}

int Dynamic_array::get_logical_size()
{
    return logical_size;
}

bool Dynamic_array::add_array_element(const int elem_index, const int new_value)
{
    if ((elem_index < 0) ||
        (elem_index >= logical_size) ||
        (arr == nullptr))
        return false;

    arr[elem_index] = new_value;
    return true;
}
int Dynamic_array::get_array_element(const int elem_index, bool& get_result)
{
    if ((elem_index < 0) ||
        (elem_index >= logical_size) ||
        (arr == nullptr))
    {
        get_result = false;
        return 0;
    }

    get_result = true;
    return arr[elem_index];
}
