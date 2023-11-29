// homework 5-1-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>


int main()
{

    //std::for_each
    std::vector<int> new_vector = { 4, 7, 9, 14, 12 };
    std::for_each(new_vector.begin(), new_vector.end(), [](int &new_vector)
        {
            if (new_vector % 2)
            {
                new_vector *= 3;
            }
            std::cout << new_vector << " ";
        });

    std::cout << "\n\n";

    std::for_each(new_vector.begin(), new_vector.end(), [](int& new_vector)
        {
             std::cout << new_vector << " ";
        });

   

}
