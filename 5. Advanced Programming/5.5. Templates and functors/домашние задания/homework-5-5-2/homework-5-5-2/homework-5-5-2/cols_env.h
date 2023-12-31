#pragma once
#include "table_exception.h"


//класс обертка дл€ колонок - элементов внутри каждого rows[n]
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

	//конструктор копировани€
	cols_env(const cols_env& old_cols_env) = delete;

	//оператор присваивани€ 
	cols_env& operator=(const cols_env& old_cols_env) = delete;

	~cols_env()
	{
		delete[] cols;
	}

	T& operator[](const int _col_num)	
	{
		//проверить индексы, выкинуть исключение
		if ((_col_num < 0) || (_col_num > cols_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		return cols[_col_num];
	}

	const T& operator[](const int _col_num) const
	{
		//проверить индексы, выкинуть исключение
		if ((_col_num < 0) || (_col_num > cols_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		return cols[_col_num];
	}


	T* cols = nullptr;
private:
	int cols_num = 0;
	
};
