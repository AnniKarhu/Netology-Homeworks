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
		//проверить индексы, выкинуть исключение
		if ((row < 0) || (col <0) || (row > rows_num-1) || (col > cols_num -1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		
		return rows[row][col];
	}

	void setElement(const int row, const int col, const T &value)
	{
		//проверить индексы, выкинуть исключение
		if ((row < 0) || (col < 0) || (row > rows_num - 1) || (col > cols_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		rows[row][col] = value;
	}

	T* operator[](const int _row_num)
	{
		//проверить индексы, выкинуть исключение
		if ((_row_num < 0)  || (_row_num > rows_num - 1) )
		{
			throw Table_Exception(); //выбросить ошибку
		}
		return rows[_row_num];
	}

	const T* operator[](const int _row_num) const
	{
		//проверить индексы, выкинуть исключение
		if ((_row_num < 0) || (_row_num > rows_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		return rows[_row_num];
	}

	

	const int size()
	{
		//а что является размером таблицы? общее количество элементов? или нужно вернуть пару - количество строк и столбцов?
		return rows_num * cols_num;
	}

	//нужны проверки
	//	на соблюдение границ массивов
	//	что указатели не равны nullptr
	//	что кол-во строк и столбцов больше 0
	
	
private:
	int rows_num = 0;
	int cols_num = 0;
	T** rows = nullptr;
	T*  cols = nullptr;	
};
