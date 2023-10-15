#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::string outstr;
	
	int size = 0;
	int value;
	

	setlocale(LC_ALL, "Russian");

	while (size <= 0)
	{
		std::cout << "¬ведите размер массива: ";
		std::cin >> size;
	}
	std::cout << "\n";

	int* int_array = new int[size];
	for (int i = 0; i < size; ++i)
	{
		std::cout << "arr[" << i << "] = ";
		std::cin >> int_array[i];
	}

	std::ofstream fout("out.txt");	
	fout << size << "\n";

	for (int i = size - 1; i >= 0; --i)
	{
		fout << int_array[i] << " ";
	}

	

	fout.close();
	delete[] int_array;
	return 0;
}