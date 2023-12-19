#pragma once

#include <iostream>
#include <cmath>
#include <vector>

template <class T>
class simple_functor
{
private:
	
	int sample = 3; //на что делим
	int num = 0;  //количество элементов, кратных sample (= 3)
	int sum = 0;  //сумма элементов, кратных sample (=3)

public:
	simple_functor()
	{

	}

	void operator()(const T value)
	{		
		std::cout << value << " ";
		
		//числа с плавающей точкой рассматриваются только при нулевом значении после запятой
		int temp_val = trunc(value);
		if ((temp_val % sample) == 0)			
		{
				++num;
				sum += value;
		}				
	}

	int get_sum()
	{
		return sum;
	}

	int get_count()
	{
		return num;
	}
};

