// homework-5-6-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <set>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::set<int> my_set;
    std::cout << "Сколько будет элементов?\n";
    std::cout << "[IN]:\n";
    int elem_num;
    std::cin >> elem_num;
    std::cout << "введите элементы:\n";
    for (int i = 0; i < elem_num; ++i)
    {
        int new_elem;
        std::cin >> new_elem;
        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> new_elem;
        }

        my_set.insert(new_elem);        
    }

    /*std::cout << "[OUT]\n";
    for (const auto& elem : my_set)
        std::cout << elem << "\n";*/

    std::cout << "[OUT]\n";
    std::set<int>::iterator it = my_set.end();
    while (it != my_set.begin())
    {
        --it;
        std::cout << *it << "\n";
    }
    
}

