#include <future>
#include <iostream>
#include <vector>
#include <algorithm>

void print_list(const std::vector<int>& src_vector);    //вывести значения на экран

template<class Iter, class PFE_Func, size_t limit_size = 25>
void parallel_for_each(Iter begin, Iter end, PFE_Func func)
{
	auto l_size = std::distance(begin, end);
	if (l_size <= limit_size)
	{
		std::for_each(begin, end, func);
		return;
	}

	auto mid = begin;
	std::advance(mid, l_size / 2);
	
	//левая часть передается в асинхронную задачу
	std::future<void> ft_res = std::async(parallel_for_each<Iter,  PFE_Func>, begin, mid, func);
	
	//правая остается в этом потоке
	parallel_for_each(mid, end, func);
	ft_res.wait();	

}


int main()
{
	std::vector<int> new_vector(10);
	print_list(new_vector);
	parallel_for_each(new_vector.begin(), new_vector.end(), [](int& n) { ++n; });
	print_list(new_vector);

	return 0;
}


//вывести значения на экран
void print_list(const std::vector<int>& src_vector)
{
	for (int i = 0; i < src_vector.size(); ++i)
	{
		std::cout << src_vector[i] << " ";
	}
	std::cout << "\n";
}
