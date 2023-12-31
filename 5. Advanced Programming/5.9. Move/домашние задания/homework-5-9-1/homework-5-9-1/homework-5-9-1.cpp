// homework-5-9-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
void move_vectors(std::vector<T>& vector_from, std::vector<T>& vector_to)
{
    vector_to = (std::vector<T>&&)vector_from;    
}

int main()
{
    std::cout << "Vector one: ";
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::for_each(one.begin(), one.end(), [](std::string elem) {std::cout << elem << "\t"; });
    std::cout << "\n";

    std::cout << "Vector two: ";
    std::vector <std::string> two;
    std::for_each(two.begin(), two.end(), [](std::string elem) {std::cout << elem << "\t"; });
    std::cout << "\n";

    std::cout << "Vector two: ";
    move_vectors(one, two);
    std::for_each(two.begin(), two.end(), [](std::string elem) {std::cout << elem << "\t"; });
    std::cout << "\n";
    
}

