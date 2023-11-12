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
public:
	explicit graph();
	~graph();

	int get_graph_size(); //������ ���������� ������ �����
	bool read_grapph_from_file(std::string file_name);
	void  clear_visited(); //�������� ���������� � ���������� ��������	
	bool dfs(int vertex, int prev = 0, bool look_for_cycle = false); //����� � ������� � ������������ �������������� ������ �����
	void bfs(int vertex); //����� � ������
	bool cycle_exists(); //���������� �� � ����� ����
};
