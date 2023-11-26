#pragma once

class Smart_array
{
protected:
    int* arr = nullptr;
    int array_size = 0;  //фактический размер массива
    int add_to_array_index = 0; //указатель на индекс для добавленя следующего элемента
public:
    explicit Smart_array(const int new_size);
    virtual ~Smart_array();
  
    virtual void add_element(const int new_value); //добавить элемент
    virtual int get_element(const int elem_index);   //получить элемент по индексу
};