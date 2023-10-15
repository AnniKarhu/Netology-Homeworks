#include <iostream>
#include <string>
#include <fstream>

int main()
{
	int cols_num = 0;
	int rows_num = 0;
	std::string instr;
	std::ifstream fin("in.txt");
	
	setlocale(LC_ALL, "Russian");

	if (!(fin.is_open()))
	{
		std::cout << "Файл не существует";
		return 0;
	}

	if (!fin.eof())
	{
		fin >> instr;
		rows_num = std::stoi(instr);	
	}

	if (!fin.eof())
	{
		fin >> instr;
		cols_num = std::stoi(instr);
	}


	if ((rows_num <= 0) || (cols_num <= 0))
	{
		std::cout << "Ошибочное количество строк или столбцов";
		return 0;
	}

	int** int_array = new int* [rows_num];
	for (int i = 0; i < rows_num; ++i)
	{
		int_array[i] = new int[cols_num];
	}

	while (!fin.eof())
	{
		for (int i = 0; i < rows_num; ++i)
			for (int j = 0; j < cols_num; ++j)
			{
				fin >> instr;
				int_array[i][j] = std::stoi(instr);
			}
	}

	for (int i = 0; i < rows_num; ++i)
	{
		for (int j = cols_num - 1; j >= 0; --j)
		{
			std::cout << int_array[i][j] << " ";			
		}

		std::cout << "\n";
	}

		


	for (int i = 0; i < rows_num; ++i)
	{
		delete[] int_array[i];
	}
	delete[] int_array;
	fin.close();

	return 0;
}