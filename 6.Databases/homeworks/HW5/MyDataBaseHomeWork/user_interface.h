#pragma once
#include <iostream>

#include "data_base.h"

int main_menu(); //������� ����
void add_new_user(Data_base& db_unit); //�������� ������ �������
void print_user_info(Data_base& db_unit); //����� ���������� � �������
void add_user_phone(Data_base& db_unit); //�������� ������� ������������� �������
void update_user_data(Data_base& db_unit); //�������� ������ � �������
void delete_user_phone(Data_base& db_unit); //������� ������� ������� 
void delete_user(Data_base& db_unit); //������� ���������� � �������

int get_user_id(Data_base& db_unit); //����� id �������

int get_search_param(); //��������� � ������������, �� ������ ��������� ���� �������

std::string get_string(std::string print_str); //�������� ������ �� ������������
