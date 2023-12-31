#pragma once
#include "table_exception.h"


//����� ������� ��� ������� - ��������� ������ ������� rows[n]
template <class T>
class cols_env
{
public:
	cols_env(int _cols_num) : cols_num(_cols_num)
	{
		cols_num = _cols_num;	
		if (_cols_num > 0)
		{			
			cols = new T[_cols_num]();
		}		
	}

	//����������� �����������
	cols_env(const cols_env& old_cols_env) = delete;

	//�������� ������������ 
	cols_env& operator=(const cols_env& old_cols_env) = delete;

	~cols_env()
	{
		delete[] cols;
	}

	T& operator[](const int _col_num)	
	{
		//��������� �������, �������� ����������
		if ((_col_num < 0) || (_col_num > cols_num - 1))
		{
			throw Table_Exception(); //��������� ������
		}
		return cols[_col_num];
	}

	const T& operator[](const int _col_num) const
	{
		//��������� �������, �������� ����������
		if ((_col_num < 0) || (_col_num > cols_num - 1))
		{
			throw Table_Exception(); //��������� ������
		}
		return cols[_col_num];
	}


	T* cols = nullptr;
private:
	int cols_num = 0;
	
};
