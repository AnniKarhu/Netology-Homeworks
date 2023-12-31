#pragma once
#include "table_exception.h"
#include "cols_env.h"

template<class T>
class table
 {
public:
	table(int _rows_num, int _cols_num) : rows_num(_rows_num), cols_num(_cols_num)
	{
		if ((_cols_num > 0) && (_rows_num > 0))
		{
			rows = new cols_env<T>*[_rows_num] ;
			
			for (int i = 0; i < _rows_num; ++i)
			{	
				rows[i] = new cols_env<T>(_cols_num);				
			}
		}
	}
	~table()
	{
		
		for (int i = 0; i < rows_num; ++i)
		{
			delete rows[i];
		}
		
		delete[] rows;
	}

	//конструктор копирования
	table(const table& old_table)
	{
		rows_num = old_table.rows_num;
		cols_num = old_table.cols_num;

		if ((cols_num > 0) && (rows_num > 0))
		{			
			rows = new cols_env<T>*[rows_num];

			for (int i = 0; i < rows_num; ++i)
			{
				rows[i] = new cols_env<T>(cols_num);
				for (int j = 0; j < cols_num; ++j)
				{
					rows[i]->cols[j] = old_table.rows[i]->cols[j];
				}
			}			
		}
	}

	//оператор присваивания 
	table& operator=(const table& old_table)
	{
		if (this != &old_table) //нет смысла присваивать объект самому себе
		{
			for (int i = 0; i < rows_num; ++i) //почистить все колонки
			{
				//На строке 60 в файле table.h вы вызываете delete[] rows[i]; нужно писать delete rows[i]; так как аллокация была не как массив а как один объект.
				
				//delete[] rows[i];
				delete rows[i];
			}

			delete[] rows; //почистить строки

			rows_num = old_table.rows_num;
			cols_num = old_table.cols_num;

			if ((cols_num > 0) && (rows_num > 0))
			{
				rows = new cols_env<T>*[rows_num];
				for (int i = 0; i < rows_num; ++i)
				{
					rows[i] = new cols_env<T>(cols_num);
					for (int j = 0; j < cols_num; ++j)
					{
						rows[i]->cols[j] = old_table.rows[i]->cols[j];
						
					}
				}
			}

		}

	}
	

	T getElement(const int row, const int col)
	{
		//проверить индексы, выкинуть исключение
		if ((row < 0) || (col < 0) || (row > rows_num - 1) || (col > cols_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}

		cols_env<T>* temp_cols = rows[row];
		T temp_value = temp_cols->cols[col]; // ->cols[col];
		return temp_value;
		
		//return rows[row]->cols[col]; 
	}

	void setElement(const int row, const int col, const T& value)
	{
		//проверить индексы, выкинуть исключение
		if ((row < 0) || (col < 0) || (row > rows_num - 1) || (col > cols_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		rows[row]->cols[col] = value;
	}

	cols_env<T>& operator[](const int _row_num)
	{
		//проверить индексы, выкинуть исключение
		if ((_row_num < 0) || (_row_num > rows_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		return *(rows[_row_num]);
	}

	const cols_env<T>& operator[](const int _row_num) const
	{
		//проверить индексы, выкинуть исключение
		if ((_row_num < 0) || (_row_num > rows_num - 1))
		{
			throw Table_Exception(); //выбросить ошибку
		}
		return *(rows[_row_num]);
	}

	const int size()
	{
		//а что является размером таблицы? общее количество элементов? или нужно вернуть пару - количество строк и столбцов?
		return rows_num * cols_num;
	}

private:
	int rows_num = 0;
	int cols_num = 0;	
	cols_env<T>** rows = nullptr;	
		
};
