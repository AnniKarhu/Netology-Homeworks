// homework-5-7-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <set>
#include <list>

template <class T>
void print_container(const T& a)
{
    for (const auto& elem : a)
    {
        std::cout << elem << " ";
    }
    
    std::cout << "\n\n";
}

template <class T>
void print_container2(const T& a)
{
    auto i = a.begin(); // итератор на начало
    
    while (i != a.end())
    {
        std::cout << *i << " ";
        ++i;
    }   

    std::cout << "\n\n";
}



int main()
{
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set); 
    print_container2(test_set);

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list);
    print_container2(test_list);

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector); 
    print_container2(test_vector);
}



