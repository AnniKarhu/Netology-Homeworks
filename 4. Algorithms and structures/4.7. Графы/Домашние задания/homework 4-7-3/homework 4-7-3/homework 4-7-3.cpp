// homework 4-7-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>

#include "graph.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	graph* new_graph = new graph();
	if (!new_graph->read_grapph_from_file("input3.txt"))
	{
		return 0;
	}

	std::cout << "Порядок обхода вершин в глубину: ";
	new_graph->dfs(0);
	new_graph->clear_visited();

	if (new_graph->cycle_exists())
	{
		std::cout << "\nВ графе есть цикл!\n";
	}
	else
	{
		std::cout << "\nВ графе нет циклов\n";
	}


	graph* second_graph = new graph();
	if (!second_graph->read_grapph_from_file("input2.txt"))
	{
		return 0;
	}

	std::cout << "Порядок обхода вершин в глубину: ";
	second_graph->dfs(0);
	second_graph->clear_visited();

	if (second_graph->cycle_exists())
	{
		std::cout << "\nВ графе есть цикл!\n";
	}
	else
	{
		std::cout << "\nВ графе нет циклов\n";
	}

	delete new_graph;
	delete second_graph;

	return 0;
}
