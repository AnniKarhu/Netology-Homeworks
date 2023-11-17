// homework 4-8-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

void top_sort(int** graph_array, int graph_size, int vertex, int*& order); //топологическая сортировка
bool dfs(int** graph_array, int graph_size, int vertex, int* visited, int* order, int &order_index); //обход в глубину


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

	int* order = new int[graph_size]();

	top_sort(vert_array, graph_size, 1, order); //топологическая сортировка
	std::cout << "Топологический порядок вершин: ";
	for (int i = graph_size-1; i >=0; --i)
	{
		std::cout << order[i] << " ";
	}

	delete[] order;

	for (int i = 0; i < graph_size; ++i)
	{
		delete[] vert_array[i];
	}
	delete[] vert_array;

}

void top_sort(int** graph_array, int graph_size, int vertex, int* &order) //топологическая сортировка
{
	if ((graph_size <= 0) ||
		(vertex <= 0) ||
		(vertex > graph_size))
	{
		return;
	}
	
	int* visited =  new int[graph_size]();
	
	int order_index = 0;

	dfs(graph_array, graph_size, 1, visited, order, order_index); //обход в глубину

	for (int v = 1; v <= graph_size; ++v)
	{
		if (!visited[v - 1])
		{
			dfs(graph_array, graph_size, v, visited, order, order_index); //обход в глубину
		}		
	}
	delete[] visited;	
}

/*graph_array - указатель на двумерный массив, содержащий граф
graph_size - количество вершин графа = размер каждого измерения массива
vertex - текущая рассматриваемая вершина
visited - указатель на массив посещенных вершин
order - указатель на массив порядка вершин - в обратном порядке
order_index - в какую ячейку добавлять следующую вершину в массив order*/
bool dfs(int** graph_array, int graph_size, int vertex, int* visited, int* order, int &order_index) //обход в глубину
{
	if ((graph_size <= 0) ||
		(vertex <= 0) ||
		(vertex > graph_size))
	{
		return false;
	}

	visited[vertex - 1] = 1; //отметить вершину пройденной
	for (int v = 1; v <= graph_size; ++v) //перебрать все вершины в массиве
	{
		if ((graph_array[vertex - 1][v - 1]) && //если существует дуга к вершине
			(!visited[v - 1])) //и эту вершину еще не посещали
		{			
			dfs(graph_array, graph_size, v, visited, order, order_index); //запустить обход из этой вершины 			
		}		
	}	
	order[order_index] = vertex;
	order_index++;
	
}
