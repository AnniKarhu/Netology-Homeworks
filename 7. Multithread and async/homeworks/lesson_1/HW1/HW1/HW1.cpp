// HW1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<thread>
#include<chrono>

using namespace std::chrono_literals;

void enqueue(int& count, const int max_customers);
void dequeue(int& count);

int main()
{
    std::cout << "Hello World!\n";
    int max_customers = 10; //максимальное число клиентов
    int customers_count = 0; //счетчик прошедших клиентов

    std::thread thread_enqueue(enqueue, std::ref(customers_count), max_customers);
    std::thread thread_dequeue(dequeue, std::ref(customers_count));

    thread_enqueue.join();
    thread_dequeue.join();

    return 0;
}

void enqueue(int& count, const int max_customers)
{    
    static int total_count = 0;
    while (total_count < max_customers)
    {
        ++count;
        ++total_count;
        std::cout << "One customer in. Customers in queue = "<< count << ". Total customers = " << total_count << "\n";
        std::this_thread::sleep_for(1050ms);
    }    
    
}

void dequeue(int& count)
{
    std::this_thread::sleep_for(10ms);
    while (count > 0)
    {
        std::this_thread::sleep_for(2000ms);
        --count;
        std::cout << "One customer out. Customers in queue = " << count << "\n";
    }
    
    
    
}