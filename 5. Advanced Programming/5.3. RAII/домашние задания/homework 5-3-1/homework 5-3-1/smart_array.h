#pragma once

class Smart_array
{
protected:
    int* arr = nullptr;
    int array_size = 0;  //����������� ������ �������
    int add_to_array_index = 0; //��������� �� ������ ��� ��������� ���������� ��������
public:
    explicit Smart_array(const int new_size);
    virtual ~Smart_array();
  
    virtual void add_element(const int new_value); //�������� �������
    virtual int get_element(const int elem_index);   //�������� ������� �� �������
};