#pragma once
#include "table_exception.h"

template<class T>
class table
{
public:
	table(int _rows_num, int _cols_num) : rows_num(_rows_num), cols_num(_cols_num)		
	{
		//assert(rows_num > 0);
		//assert(cols_num > 0);

		if ((_cols_num > 0) && (_rows_num > 0))
		{
			rows = new T* [_rows_num];			
			for (int i = 0; i < _rows_num; ++i)
			{
				rows[i] = new T[_cols_num]();
			}
		}
	}
	~table()
	{
		for (int i = 0; i < rows_num; ++i)
		{
			delete[] rows[i];
		}

		delete[] rows;
	}

	table(const table&) = delete;
	table& operator=(const table&) = delete;
	
	T getElement(const int row, const int col) 
	{
		//��������� �������, �������� ����������
		if ((row < 0) || (col <0) || (row > rows_num-1) || (col > cols_num -1))
		{
			throw Table_Exception(); //��������� ������
		}
		
		return rows[row][col];
	}

	void setElement(const int row, const int col, const T &value)
	{
		//��������� �������, �������� ����������
		if ((row < 0) || (col < 0) || (row > rows_num - 1) || (col > cols_num - 1))
		{
			throw Table_Exception(); //��������� ������
		}
		rows[row][col] = value;
	}

	T* operator[](const int _row_num)
	{
		//��������� �������, �������� ����������
		if ((_row_num < 0)  || (_row_num > rows_num - 1) )
		{
			throw Table_Exception(); //��������� ������
		}
		return rows[_row_num];
	}

	const T* operator[](const int _row_num) const
	{
		//��������� �������, �������� ����������
		if ((_row_num < 0) || (_row_num > rows_num - 1))
		{
			throw Table_Exception(); //��������� ������
		}
		return rows[_row_num];
	}

	

	const int size()
	{
		//� ��� �������� �������� �������? ����� ���������� ���������? ��� ����� ������� ���� - ���������� ����� � ��������?
		return rows_num * cols_num;
	}

	//����� ��������
	//	�� ���������� ������ ��������
	//	��� ��������� �� ����� nullptr
	//	��� ���-�� ����� � �������� ������ 0
	
	
private:
	int rows_num = 0;
	int cols_num = 0;
	T** rows = nullptr;
	T*  cols = nullptr;	
};
