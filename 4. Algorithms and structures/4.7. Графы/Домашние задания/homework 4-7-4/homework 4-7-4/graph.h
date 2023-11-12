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
	int* stack_adjacency = nullptr; //������ - ���� ��� ������ ������� ����������� ��������� ������ ������ ���������� ���������
	int stack_adjacency_index = 0;  //������ ������� ���������� �������� ������� stack_adjacency
public:
	explicit graph();
	~graph();

	int get_graph_size(); //������ ���������� ������ �����
	bool read_grapph_from_file(std::string file_name);
	void clear_visited(); //�������� ���������� � ���������� ��������	
	bool dfs(int vertex, int prev = 0, bool look_for_cycle = false); //����� � ������� � ������������ �������������� ������ �����
	int dfs_adjacency(int vertex); //����� � ������� - ������� ��������� ��������� 
	void bfs(int vertex); //����� � ������ 
	bool cycle_exists(); //���������� �� � ����� ����
	void print_adjacency(); //������� �������������� ������ ����������� ���������
};
