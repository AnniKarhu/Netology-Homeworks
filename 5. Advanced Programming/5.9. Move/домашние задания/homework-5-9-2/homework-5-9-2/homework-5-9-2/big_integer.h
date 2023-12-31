#pragma once
#include <iostream>
#include <vector>

class big_integer
{
private:
	std::vector<int>* big_vector = nullptr; // = { 0 }; //
	bool value_is_valid() const; // = true; //���� ��������� �������� false, ���� ����� �� �������, ��������, ��� �������� �� ���� ������� ������������� ������ � �����
	const int elem_size = 4; //������� �������� ����� ������ ���� ���� -       ������� big_vector
	int sign = 1; //���� �����
public:
	//std::string str_value = "0";
	
	big_integer(std::string value_str);
	big_integer(const big_integer& other);//����������� �����������
	big_integer(big_integer&& other);	// ����������� �����������

	~big_integer();
	
	big_integer& operator=(const big_integer& other);  //�������� ������������ 
	big_integer& operator=(big_integer&& other);       // �������� ������������� ������������
	
	big_integer operator+(const big_integer& other); //�������� ��������
	big_integer operator-(const big_integer& other); //�������� ���������
	big_integer operator*(const int& other); //�������� ���������

	//bool operator>(const big_integer& other) const;
	bool module_greater(const big_integer& first, const big_integer& second); //��������� ����� �� ������

	int get_size() const;
	//std::string get_elements(); 
	
	friend std::ostream& operator<<(std::ostream& os, const big_integer& my_big_int); //����� �������� �����
};