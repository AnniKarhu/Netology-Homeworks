// homework-5-7-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include <vector>


void print_vector(std::vector<int> m_vector, std::string temp_str); //вывести массив на экран
int pivoting_vector(std::vector<int>& m_vector, int left, int right);
void quick_sort_vector(std::vector<int>& m_vector, int left, int right);
void swap(int& A, int& B);

int main()
{
    setlocale(LC_ALL, "rus");
   
    std::vector<int> my_vector = { 1, 1, 2, 5, 6, 1, 2, 4 };
    print_vector(my_vector, "[IN]: ");
    quick_sort_vector(my_vector, 0, my_vector.size() - 1);
    

    auto it = std::unique(my_vector.begin(), my_vector.end());
    my_vector.erase(it, my_vector.end()); 
    print_vector(my_vector, "[OUT]: ");    

}


int pivoting_vector(std::vector<int>& m_vector, int left, int right)
{
    // Пивот -  крайний правый элемент  массива
    int pivot = m_vector[right];

    // элементы массива меньше пивота перекидываются влево от индекса temp
    // элементы массива больше пивота перекидываются вправо от индекса temp
    int temp = left;

    // если элемент массива < = pivot, индекс temp увеличивается, и  элемент меняется местами с пивотом
    for (int i = left; i < right; i++)
    {
        if (m_vector[i] <= pivot)
        {
            swap(m_vector[i], m_vector[temp]);
            temp++;
        }
    }

    // поменять местами  с пивотом
    swap(m_vector[temp], m_vector[right]);

    // вернуть номер нового пивота
    return temp;
}


void quick_sort_vector(std::vector<int>& m_vector, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    // переставить элементы
    int pivot = pivoting_vector(m_vector, left, right);

    // сортировать подмассив слева от пивота
    quick_sort_vector(m_vector, left, pivot - 1);

    // сортировать подмассив справа от пивота
    quick_sort_vector(m_vector, pivot + 1, right);
}

void swap(int& A, int& B)
{
    int temp = A;
    A = B;
    B = temp;
}


void print_vector(std::vector<int> m_vector, std::string temp_str) //вывести вектор на экран
{
    std::cout << temp_str;
    for (const auto& elem : m_vector) 
    {
        std::cout << elem << ' '; 
    }

    std::cout << "\n";
}