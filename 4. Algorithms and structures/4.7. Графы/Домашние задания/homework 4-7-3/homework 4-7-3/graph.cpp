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

int graph::get_graph_size() //узнать количество вершин графа
{
	return graph_size;
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

void  graph::clear_visited() //сбросить информацию о посещенных вершинах
{
	for (int i = 0; i < graph_size; ++i)
	{
		visited_vertices[i] = 0;
	}
}

bool graph::dfs(int vertex, int prev, bool look_for_cycle) //обход в глубину с возможностью одновременного поиска цикла
{
	if ((vertex > (graph_size -1)) || 
		(vertex < 0)) // индекс массива не может быть меньше 0
	{
		return false;
	}

	visited_vertices[vertex] = 1; //отметить вершину пройденной
	
	if (!look_for_cycle)
	{
		std::cout << vertex + 1 << " ";
	}
	
	for (int v = 0; v < graph_size; ++v)
	{	
		if (vert_array[vertex][v]) //если существует ребро к смежной вершине 
		{
			if (!visited_vertices[v]) //если эту вершину еще не посещали
			{
				prev = vertex;
				dfs(v, prev, look_for_cycle); //запустить обход
			}
			else //смежную вершину уже посещали 
			{
				if ((look_for_cycle) && //обход ради поиска цикла
					(v != prev)) //смежная вершина не та, из которой пришли
				{
					return true;
				}
			}
		}
	}

	//проверить вершины других компонент связности
	for (int i = 0; i < graph_size; ++i)
	{
		if (!visited_vertices[i]) //вершина осталась непосещенной - значит, она из другого компонента связности
		{
			dfs(i, prev, look_for_cycle); //запустить обход
		}
	}

	return false;
}

void graph::bfs(int vertex)  //обход в ширину
{
	
	if ((vertex > (graph_size)) ||
		(vertex < 1)) // индекс массива не может быть меньше 0, а номер вершины - меньше 1
	{
		return;
	}
	
	Dynamic_array queue(0, graph_size); //класс обертка для работы с динамическим массивом

	queue.append_to_dynamic_array(vertex); //добавить еще один элемент к существующему массиву - первую вершину в очередь на обход
	
	int queue_index_next = 0; //индекс очереди - откуда берем следующую вершину для обхода
	
	while (queue[queue_index_next])   //в ячейке 0, если нет следующего элемента для обхода		  
	{	
		vertex = queue[queue_index_next];

		if (!visited_vertices[vertex - 1]) //если вершина еще не пройдена
		{
			visited_vertices[vertex-1] = 1; //отметить вершину пройденной
			std::cout << vertex << " ";
			
			//проверка и постановка в очередь смежных вершин
			for (int v = 0; v < graph_size; ++v)
			{
				if (vert_array[v][vertex-1]) //если существует ребро к смежной вершине 
				{
					if (!visited_vertices[v]) //если эту вершину еще не посещали
					{
						queue.append_to_dynamic_array(v+1);
					}
				}
			}
		}		

		++queue_index_next;			
	}
 }

bool graph::cycle_exists() //существует ли в графк цикл
{
	return dfs(0, 0, true);	 
}