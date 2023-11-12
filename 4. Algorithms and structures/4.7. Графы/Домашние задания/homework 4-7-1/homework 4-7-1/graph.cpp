#include "graph.h"
#include "Dynamic_array.h"

graph::graph()
{

}
graph::~graph()
{
	for (int i = 0; i < graph_size; ++i)
	{
		delete[]	vert_array[i];
	}
	delete[] vert_array;

	delete[] visited_vertices;
}

bool graph::get_graph_ready()
{
	return false; 
}

bool graph::read_grapph_from_file(std::string file_name)
{
	std::ifstream fin(file_name);
	std::string input_str;

	if (!(fin.is_open()))
	{
		std::cout << "Файл не существует";
		return false;
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
			return false;
		}
		 
		if (temp > 0)
		{
			graph_size = temp; // количество вершин графа
			vert_array = new int*[graph_size]; //массив для хранения данных графа
			visited_vertices = new int[graph_size]();//массив посещенных вершин			
			
			//считать данные о смежных вершинах из файла в массив
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
						std::cout << "Странные данные в файле: " << input_str <<"\n";
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

	graph_ready = true;
	return true;
	
}

void graph::dfs(int vertex)
{
	if ((vertex > (graph_size -1)) || 
		(vertex < 0)) // индекс массива не может быть меньше 0
	{
		return;
	}
	
	visited_vertices[vertex] = 1; //отметить вершину пройденной
	std::cout << vertex+1 << " ";
	for (int v = 0; v < graph_size; ++v)
	{	
		if (vert_array[vertex][v]) //если существует ребро к смежной вершине 
		{
			if (!visited_vertices[v]) //если эту вершину еще не посещали
			{
				dfs(v); //запустить обход
			}
		}		
	}

	//проверить вершины других компонент связности
	for (int i = 0; i < graph_size; ++i)
	{
		if (!visited_vertices[i]) //вершина осталась непосещенной - значит, она из другого компонента связности
		{
			dfs(i); //запустить обход
		}
	}
}