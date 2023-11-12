// homework 4-7-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include "graph.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	graph* new_graph = new graph();
	if (!new_graph->read_grapph_from_file("input.txt"))
	{
		return 0;
	}	

	std::cout << "Порядок обхода вершин: ";
	new_graph->dfs(0);

	delete new_graph;
		
	return 0;
}
