#pragma once
#include <iostream>
#include <fstream>
#include <string>

class graph
{
private:
	int graph_size = 0;
	bool graph_ready = false;
	int** vert_array = nullptr;
	int* visited_vertices = nullptr;
	int adjacency_num = 1;
	int* stack_adjacency = nullptr; //массив - стек для записи очереди прохождения элементов внутри одного компонента связности
	int stack_adjacency_index = 0;  //индекс первого свободного элемента массива stack_adjacency
public:
	explicit graph();
	~graph();

	int get_graph_size(); //узнать количество вершин графа
	bool read_grapph_from_file(std::string file_name);
	void clear_visited(); //сбросить информацию о посещенных вершинах	
	bool dfs(int vertex, int prev = 0, bool look_for_cycle = false); //обход в глубину с возможностью одновременного поиска цикла
	int dfs_adjacency(int vertex); //обход в глубину - подсчет компонент связности 
	void bfs(int vertex); //обход в ширину 
	bool cycle_exists(); //существует ли в графе цикл
	void print_adjacency(); //вывести принадлежность вершин компонентам связности
};
