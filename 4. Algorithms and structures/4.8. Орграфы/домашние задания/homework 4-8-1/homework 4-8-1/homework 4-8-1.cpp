// homework 4-8-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

int main()
{
	setlocale(LC_ALL, "rus");
	
	//считать данные из файла
	std::ifstream fin("input.txt");
	std::string input_str;
	int graph_size = 0;
	int** vert_array = nullptr;

	if (!(fin.is_open()))
	{
		std::cout << "Файл не существует";
		return 0;
	}

	if (!fin.eof())
	{
		fin >> input_str;
		int temp = 0;
		try
		{
			temp = std::stoi(input_str);//исключение, если не число
		}
		catch (...)
		{
			std::cout << "Странные данные в файле\n";
			return 0;
		}

		if (temp > 0)
		{
			graph_size = temp; // количество вершин графа
			vert_array = new int* [graph_size]; //массив для хранения данных графа
			
			//считать данные о вершинах из файла в массив
			for (int i = 0; i < graph_size; ++i)
			{
				vert_array[i] = new int[graph_size];
				for (int j = 0; j < graph_size; ++j)
				{
					if (fin.eof())
					{
						std::cout << "Не хватает данных в файле";
						fin.close();
						return false;
					}

					fin >> input_str;
					try
					{
						vert_array[i][j] = std::stoi(input_str);
					}
					catch (...)
					{
						std::cout << "Странные данные в файле: " << input_str << "\n";
						return false;
					}
				}
			}

			fin.close();
		}
		else
		{
			std::cout << "Ошибочный размер графа";
			return false;
		}
	}
    
	//вывод графа на консоль
	std::cout << "Текстовый вид орграфа :\n";

	for (int i = 0; i < graph_size; ++i) //для каждой вершины
	{
		int v_counter = 0;
		std::cout << i + 1 << ": ";
		for (int j = 0; j < graph_size; ++j) //перебрать все исходящие
		{
			if (vert_array[i][j])
			{
				++v_counter;
				std::cout << j +1 << " ";
			}
		}

		if (v_counter) //была определена хоть одна вершина
		{
			std::cout << "\n";
		}
		else//не было определено ни одной вершины, в которую можно попасть из текущей
		{
			std::cout << "нет\n";
		}		
	}
    
    
	for (int i = 0; i < graph_size; ++i)
	{
		delete[] vert_array[i];
	}
	delete[] vert_array;

}
