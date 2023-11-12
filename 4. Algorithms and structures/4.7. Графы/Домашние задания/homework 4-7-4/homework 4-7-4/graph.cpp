#include "graph.h"
#include "Dynamic_array.h"

graph::graph()
{

}
graph::~graph()
{
	for (int i = 0; i < graph_size; ++i)
	{
		delete[] vert_array[i];
	}
	delete[] vert_array;

	delete[] visited_vertices;
	delete[] stack_adjacency;
}

int graph::get_graph_size() //������ ���������� ������ �����
{
	return graph_size;
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
			stack_adjacency = new int[graph_size](); //������ ���� - ������� ����������� ��������� ������ ������ ���������� ���������

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

void  graph::clear_visited() //�������� ���������� � ���������� ��������
{
	for (int i = 0; i < graph_size; ++i)
	{
		visited_vertices[i] = 0;
		//stack_adjacency[i] = 0;
	}
	adjacency_num = 1;
}

bool graph::dfs(int vertex, int prev, bool look_for_cycle) //����� � ������� � ������������ �������������� ������ �����
{
	if ((vertex > (graph_size - 1)) ||
		(vertex < 0)) // ������ ������� �� ����� ���� ������ 0
	{
		return false;
	}

	visited_vertices[vertex] = 1; //�������� ������� ����������

	if (!look_for_cycle)
	{
		std::cout << vertex + 1 << " ";
	}

	for (int v = 0; v < graph_size; ++v)
	{
		if (vert_array[vertex][v]) //���� ���������� ����� � ������� ������� 
		{
			if (!visited_vertices[v]) //���� ��� ������� ��� �� ��������
			{
				prev = vertex;
				dfs(v, prev, look_for_cycle); //��������� �����
			}
			else //������� ������� ��� �������� 
			{
				if ((look_for_cycle) && //����� ���� ������ �����
					(v != prev)) //������� ������� �� ��, �� ������� ������
				{
					return true;
				}
			}
		}
	}

	//��������� ������� ������ ��������� ���������
	for (int i = 0; i < graph_size; ++i)
	{
		if (!visited_vertices[i]) //������� �������� ������������ - ������, ��� �� ������� ���������� ���������
		{
			dfs(i, prev, look_for_cycle); //��������� �����
		}
	}

	return false;
}

int graph::dfs_adjacency(int vertex) //����� � ������� ����� ���������� ���������
{
	//static int dfs_counter = 0;
	//dfs_counter++;

	if ((vertex > (graph_size)) ||
		(vertex < 1)) // ������ ������� �� ����� ���� ������ 0
	{
		return 0;
	}

	visited_vertices[vertex-1] = adjacency_num; //�������� ������� ����������
	
	//�������� ������� � ����	
	if (stack_adjacency[stack_adjacency_index] != vertex)
	{
		stack_adjacency[stack_adjacency_index] = vertex;
		++stack_adjacency_index;
	}	
 
	for (int v = 0; v < graph_size; ++v)
	{
		if (vert_array[vertex-1][v]) //���� ���������� ����� � ������� ������� 
		{
			if (!visited_vertices[v]) //���� ��� ������� ��� �� ��������
			{	
				dfs_adjacency(v+1); //��������� �����
			}			
		}
	}
	
	while (stack_adjacency_index) //
	{
		//stack_adjacency[stack_adjacency_index] = 0;
		--stack_adjacency_index;
		dfs_adjacency(stack_adjacency[stack_adjacency_index]); //��������� ����� ��� ���������� ������� ��� ��� - ����� ��������� � ������������
	}	

	//��������� ������� ������ ��������� ���������
	for (int i = 0; i < graph_size; ++i)
	{
		if (!visited_vertices[i]) //������� �������� ������������ - ������, ��� �� ������� ���������� ���������
		{
			++adjacency_num;
			dfs_adjacency(i+1); //��������� �����
		}
	}	

	//dfs_counter--;
	return adjacency_num;
}

void graph::bfs(int vertex)  //����� � ������
{
	
	if ((vertex > (graph_size)) ||
		(vertex < 1)) // ������ ������� �� ����� ���� ������ 0, � ����� ������� - ������ 1
	{
		return;
	}	

	Dynamic_array queue(0, graph_size); //����� ������� ��� ������ � ������������ ��������

	queue.append_to_dynamic_array(vertex); //�������� ��� ���� ������� � ������������� ������� - ������ ������� � ������� �� �����
	
	int queue_index_next = 0; //������ ������� - ������ ����� ��������� ������� ��� ������
	
	while (queue[queue_index_next])   //� ������ 0, ���� ��� ���������� �������� ��� ������		  
	{	
		vertex = queue[queue_index_next];

		if (!visited_vertices[vertex - 1]) //���� ������� ��� �� ��������
		{
			visited_vertices[vertex-1] = 1; //�������� ������� ����������
			std::cout << vertex << " ";
			
			//�������� � ���������� � ������� ������� ������
			for (int v = 0; v < graph_size; ++v)
			{
				if (vert_array[v][vertex-1]) //���� ���������� ����� � ������� ������� 
				{
					if (!visited_vertices[v]) //���� ��� ������� ��� �� ��������
					{
						queue.append_to_dynamic_array(v+1);
					}
				}
			}
		}		

		++queue_index_next;			
	}
 }

bool graph::cycle_exists() //���������� �� � ����� ����
{
	return dfs(0, 0, true);	 
}

void graph::print_adjacency() //������� �������������� ������ ����������� ���������
{
	std::cout << "�������������� ������ ����������� ���������: \n";
	clear_visited(); //�������� ���������� ����������, ���� ��� ����������� ������		
	int num = dfs_adjacency(1); 	

	//������ ���� ���������� �  ����������� ���������
	for (int i = 0; i < graph_size; ++i)
	{
		std::cout << i + 1 << " - " << visited_vertices[i] << "\n";
	}
	std::cout << "���������� ����������� ��������� � �����: " << num << "\n";
}