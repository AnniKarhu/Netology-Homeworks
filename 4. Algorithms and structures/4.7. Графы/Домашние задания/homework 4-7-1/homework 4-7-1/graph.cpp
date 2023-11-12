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
		std::cout << "���� �� ����������";
		return false;
	}

	if (!fin.eof())
	{
		fin >> input_str;
		int temp = 0;
		try
		{
			temp = std::stoi(input_str);//����������, ���� �� �����
		}
		catch (...)
		{
			std::cout << "�������� ������ � �����\n";
			return false;
		}
		 
		if (temp > 0)
		{
			graph_size = temp; // ���������� ������ �����
			vert_array = new int*[graph_size]; //������ ��� �������� ������ �����
			visited_vertices = new int[graph_size]();//������ ���������� ������			
			
			//������� ������ � ������� �������� �� ����� � ������
			for (int i = 0; i < graph_size; ++i)
			{
				vert_array[i] = new int[graph_size];
				for (int j = 0; j < graph_size; ++j)
				{
					if (fin.eof())
					{
						std::cout << "�� ������� ������ � �����";	
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
						std::cout << "�������� ������ � �����: " << input_str <<"\n";
						return false;
					}
					
				}
			}			

			fin.close();
		}
		else
		{
			std::cout << "��������� ������ �����";
			return false;
		}		
	}

	graph_ready = true;
	return true;
	
}

void graph::dfs(int vertex)
{
	if ((vertex > (graph_size -1)) || 
		(vertex < 0)) // ������ ������� �� ����� ���� ������ 0
	{
		return;
	}
	
	visited_vertices[vertex] = 1; //�������� ������� ����������
	std::cout << vertex+1 << " ";
	for (int v = 0; v < graph_size; ++v)
	{	
		if (vert_array[vertex][v]) //���� ���������� ����� � ������� ������� 
		{
			if (!visited_vertices[v]) //���� ��� ������� ��� �� ��������
			{
				dfs(v); //��������� �����
			}
		}		
	}

	//��������� ������� ������ ��������� ���������
	for (int i = 0; i < graph_size; ++i)
	{
		if (!visited_vertices[i]) //������� �������� ������������ - ������, ��� �� ������� ���������� ���������
		{
			dfs(i); //��������� �����
		}
	}
}