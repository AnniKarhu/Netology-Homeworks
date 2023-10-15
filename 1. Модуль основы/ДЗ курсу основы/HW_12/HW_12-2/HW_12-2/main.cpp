#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string instr;
	std::ifstream fin("in.txt");
	int size = 0;
	int value;

	setlocale(LC_ALL, "Russian");

	if (!(fin.is_open()))
	{
		std::cout << "Файл не существует";
		return 0;
	}

	if (!fin.eof())
	{
		fin >> instr;
		size = std::stoi(instr);
		//std::cout << "size = " << size << "\n";		
	}

	if (size <= 0)
	{
		std::cout << "Ошибочная длина массива";
		return 0;
	}

	int* int_array = new int[size];

	int i = 0;
	while (!(fin.eof())  && (i < size))
	{
		fin >> instr;
		int_array[i] = std::stoi(instr);
	
		++i;
	}

	std::cout << "\n";

	
	std::cout << "\n";
	

	for (--i; i >= 0; --i)
	{
		
		std::cout << int_array[i] << " ";
	}

	fin.close();
	delete[] int_array;
	return 0;
}