#pragma once

#include <iostream>
#include <cmath>
#include <vector>

template <class T>
class simple_functor
{
public:
	simple_functor(T* _elem_ptr, int _elem_num) : elem_ptr(_elem_ptr), elem_num(_elem_num)
	{
	}

	void operator()()
	{
		if (elem_ptr != nullptr)
		{
			num = 0;  //количество элементов, кратных sample (= 3)
			sum = 0;  //сумма элементов, кратных sample (=3)
			
			for (int i=0; i < elem_num; ++i)
			{
				std::cout << elem_ptr[i] << "\t";
				
				//числа с плавающей точкой рассматриваются только при нулевом значении после запятой
				int temp_val = trunc(elem_ptr[i]);
				if ((temp_val / elem_ptr[i]) == 1)
				{
					if ((temp_val % sample) == 0)
					{
						++num;
						sum += elem_ptr[i];
					}
				}

				
			}
			std::cout << "\n";
			//std::cout << "get_sum() = " << sum << "\n";
			//std::cout << "get_num() = " << num << "\n";
		}		
	}

	int get_sum()
	{
		return sum;
	}

	int get_num()
	{
		return num;
	}
	

private:
	T* elem_ptr = nullptr; //указатель на массив
	int elem_num = 0; //количество перебираемых элементов
	int sample = 3; //на что делим
	int num;  //количество элементов, кратных sample (= 3)
	int sum;  //сумма элементов, кратных sample (=3)
};

template <class T>
class simple_functor <std::vector<T>>
{
public:
	simple_functor(std::vector<T>& _new_vector) : new_vector(_new_vector)
	{
	}

	void operator()()
	{
		
			num = 0;  //количество элементов, кратных sample (= 3)
			sum = 0;  //сумма элементов, кратных sample (=3)

			for (const auto& elem: new_vector)
			{
				std::cout << elem << "\t";

				//числа с плавающей точкой рассматриваются только при нулевом значении после запятой
				int temp_val = trunc(elem);
				if ((temp_val / elem) == 1)
				{
					if ((temp_val % sample) == 0)
					{
						++num;
						sum += elem;
					}
				}


			}
			std::cout << "\n";
			//std::cout << "get_sum() = " << sum << "\n";
			//std::cout << "get_num() = " << num << "\n";
		
	}

	int get_sum()
	{
		return sum;
	}

	int get_num()
	{
		return num;
	}


private:
	std::vector<T> new_vector;
	int sample = 3; //на что делим
	int num;  //количество элементов, кратных sample (= 3)
	int sum;  //сумма элементов, кратных sample (=3)
};