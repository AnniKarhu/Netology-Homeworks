#pragma once

#include "smart_array.h"

class Smart_array2 : public Smart_array
{
private:
    int logical_size = 0;
    void enlarge_array_size_x2(); //��������� ����������� ������ �������
public:
    explicit Smart_array2(const int new_size);
    ~Smart_array2() override;
  
    void add_element(const int new_value) override; //�������� �������
    int get_element(const int elem_index) override; //�������� ������� �� �������
    void print_array(); //������� �������� �������   
};