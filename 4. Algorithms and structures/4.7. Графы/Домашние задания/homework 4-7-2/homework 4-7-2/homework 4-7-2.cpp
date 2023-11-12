// homework 4-7-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>

#include "graph.h"

int get_int_value(int max_value); //получить от пользователя номер вершины

int main() 
{
	setlocale(LC_ALL, "Russian");

	graph* new_graph = new graph();
	if (!new_graph->read_grapph_from_file("input.txt"))
	{
		return 0;
	}

	std::cout << "Порядок обхода вершин в глубину: ";
	new_graph->dfs(0);
	new_graph->clear_visited();
	unsigned int vert_num = 0;
	while (!vert_num)
	{
		std::cout << "\nВ графе " << new_graph->get_graph_size() << " вершин. Введите номер вершины, с которой начнётся обход : ";
		vert_num = get_int_value(new_graph->get_graph_size()); //получить от пользователя номер вершины;
	}
	

	std::cout << "\nПорядок обхода вершин в ширину: ";
	new_graph->bfs(vert_num);

	delete new_graph;

	return 0;
}

int get_int_value(int max_value) //получить от пользователя номер вершины - число типа int от 1 до max_value. 0 - неудача.
{	
	int temp_value = 0;
	
	std::cin >> temp_value;
	if (std::cin.fail())
	{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			
			temp_value = 0;
	}

	if ((temp_value < 0) ||
			(temp_value > max_value))
	{
			temp_value = 0;
	}

	return temp_value;
}