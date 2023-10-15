#include <iostream>
#include <fstream>

int main()
{
	std::string instr;
	std::ifstream fin ("in.txt");

	setlocale(LC_ALL, "Russian");

	if (!(fin.is_open()))
	{
		std::cout << "Файл не существует";
		return 0;
	}

	while (!(fin >> instr).eof())
	{
		std::cout << instr << "\n";
	}
	
	fin.close();
	return 0;
}