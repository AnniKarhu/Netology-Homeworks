/*
В данной задаче если асинхронно выполняется только поиск минимального значения, все действия все равно выполняются последовательно,
нет преимуществ от запуска алгоритма поиска в функции async, потому что алгоритм сортировки не может продвинуться дальше раньше,
чем завершится поиск минимального значения.

целесообразнее было бы саму сортировку реализовать как асинхронную задачу, тогда основной поток мог бы параллельно выполнять какие-то другие действия.


*/

#include <iostream>
#include <vector>
#include <random>
#include <future>

void fill_unordered_list(std::vector<int>& src_vector); //заполнить массив случайными числами
void print_list(const std::vector<int>& src_vector);    //вывести значения на экран
void get_min_value_index(const std::vector<int>& src_vector, int pos, std::promise<int> prom);  //найти индекс минимального элемента
void sort_list(std::vector<int>& src_vector); //Сортировка выбором


int main()
{
    std::vector<int> new_vector(100);
    fill_unordered_list(new_vector);
    print_list(new_vector);
    sort_list(new_vector); //Сортировка выбором
    print_list(new_vector);
}

//заполнить массив случайными числами
void fill_unordered_list(std::vector<int>& src_vector)
{
    int l_size = src_vector.size();
    for (int i = 0; i < l_size; ++i)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 1000);

        int val = dist(gen);
        
        src_vector[i] = val;
    }
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


//найти индекс минимального элемента
//pos - номер позиции, от которой нужно начинать искать - до конца массива
void get_min_value_index(const std::vector<int>& src_vector, int pos, std::promise<int> prom)
{
    int l_size = src_vector.size();
    if (pos >= l_size)
    {
        prom.set_value(0);
        return;
    }

    int min_value_index = pos;
    for (int i = 0; i + pos < l_size; ++i)
    {
        if (src_vector[i + pos] < src_vector[min_value_index])
        {
            min_value_index = i + pos;
        }
    }

    prom.set_value(min_value_index);
    return;
}

//Сортировка выбором
void sort_list(std::vector<int>& src_vector)
{
    if (src_vector.empty()) return;

    int pos = 0;

    while (pos < src_vector.size())
    {
        std::promise<int> prom;
        std::future<int> ft_prom = prom.get_future();
        auto fut = std::async(get_min_value_index, src_vector, pos, std::move(prom));

        int new_index = ft_prom.get();
        std::swap(src_vector[pos], src_vector[new_index]);

        ++pos;
    }
}
