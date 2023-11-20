// homework 5-2-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

struct point
{
	double m_x;
	double m_y;
	point(double x, double y)
	{
		m_x = x;
		m_y = y;
	}
};

void print_point(const point& point_object);

int main()
{
	//int i;
	for (int i = 0; i < 5; i++)
	{			
		point my_point(i, 2 * i);
		print_point(my_point);
	}
	return 0;
}

void print_point(const point& point_object) 
{
	std::cout << "x:" << point_object.m_x << ", y: " << point_object.m_y << std::endl;
}