#include "smart_array.h"
#include "smart_array2.h"
#include "array_exception.h"

Smart_array2::Smart_array2(const int new_size) : Smart_array(new_size*2) //����������� ������ ������� � 2 ���� ������ - �� ������ �������� ���������� ����� ��������� ����� �������
{
    //���� ��� �������� ������� ������ ������ ������ 0 - ����� ��� ����� ������������� ����������� �������� ���������� �������� 
    if (new_size == 0)
    {
        arr = new int[1](); //������� ������ ������������ ������� =1
        array_size = 1;
    }   
    else if (new_size > 0)
    {
        logical_size = new_size;
    }
    
}

Smart_array2::~Smart_array2()
{
    
}

int Smart_array2::get_element(const int elem_index)
{
    if ((elem_index < 0) ||
        (elem_index >= logical_size) ||
        (arr == nullptr))
    {
        throw Array_Exception(); //��������� ������
    }

    return arr[elem_index];
}


void Smart_array2::add_element(const int new_value)
{
    if (arr == nullptr) //�� �����-�� ������� ������ �� ��������
    {
        throw Array_Exception(); //��������� ������
    }
    
    if (array_size == logical_size) //������ ��������� ��������, ������ ���
    {
        enlarge_array_size_x2(); //��������� ����������� ������ � 2 ����
    }

    arr[add_to_array_index] = new_value;    
    ++add_to_array_index;
    if (logical_size < add_to_array_index)
    {
        logical_size = add_to_array_index;
    }
    
 }

void Smart_array2::enlarge_array_size_x2() //��������� ����������� ������ ������� � 2 ����
{
    //������������ ����� ������ � 2 ���� ������ �����������
    int* new_arr = nullptr;
    array_size *= 2;
    new_arr = new int[array_size]();

    //����������� �������� �� ������� �������
    for (int i = 0; i <= add_to_array_index; ++i)
    {
        new_arr[i] = arr[i];
    }

    delete[] arr;  //���������� ������ ������� �������
    arr = new_arr; //������������� ���������
}

void Smart_array2::print_array() //������� �������� �������   
{
    for (int i = 0; i < array_size; ++i)
    {
        if (i < add_to_array_index)
        {
            std::cout << arr[i] << " ";
        }
        else
        {
            std::cout << "_" << " ";
        }
    }
    std::cout << "\n\n";
}

