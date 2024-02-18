// HW1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic> 

using namespace std::chrono_literals;

void enqueue(std::atomic<int>& count, const int max_customers, std::memory_order mem_order);
void dequeue(std::atomic<int>& count, std::memory_order mem_order);

void enqueue3(std::atomic<int>& count, const int max_customers);
void dequeue3(std::atomic<int>& count);

int main()
{
    std::cout << "Hello World!\n";
    int max_customers = 10; //максимальное число клиентов
    std::atomic<int> customers_count = 0; //счетчик прошедших клиентов
    
    std::cout << "memory_order = memory_order_seq_cst\n";
    auto start = std::chrono::steady_clock::now();
    std::thread thread_enqueue(enqueue, std::ref(customers_count), max_customers, std::memory_order_seq_cst);
    std::thread thread_dequeue(dequeue, std::ref(customers_count), std::memory_order_seq_cst);    
    
    thread_enqueue.join();
    thread_dequeue.join();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "s\n";

    std::cout << "\nmemory_order = memory_order_relaxed\n";
    customers_count = 0;
    start = std::chrono::steady_clock::now();
    std::thread thread_enqueue_2(enqueue, std::ref(customers_count), max_customers, std::memory_order_relaxed);
    std::thread thread_dequeue_2(dequeue, std::ref(customers_count), std::memory_order_relaxed);

    thread_enqueue_2.join();
    thread_dequeue_2.join();

    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "s\n";

    std::cout << "\nmemory_order = memory_order_acquire + memory_order_release\n";
    start = std::chrono::steady_clock::now();
    std::thread thread_enqueue3(enqueue3, std::ref(customers_count), max_customers);
    std::thread thread_dequeue3(dequeue3, std::ref(customers_count));

    thread_enqueue3.join();
    thread_dequeue3.join();

    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << elapsed_seconds.count() << "s\n";


    return 0;
}

void enqueue(std::atomic<int>& count, const int max_customers, std::memory_order mem_order)
{    
   // static int total_count = 0;
    int total_count = 0;
    while (total_count < max_customers)
    {
         count.store(count.load(mem_order) + 1, mem_order);
        //++count;
        ++total_count;
        
        std::string temp_str = "One customer in. Customers in queue = "  + std::to_string(count.load(mem_order)) + ". Total customers = " + std::to_string(total_count) + "\n";
        std::cout << temp_str;
        std::this_thread::sleep_for(200ms);
    }    
    
}

void dequeue(std::atomic<int>& count, std::memory_order mem_order)
{
      
    std::this_thread::sleep_for(10ms);
    while (count.load(mem_order)) // > 0)
    {
        std::this_thread::sleep_for(400ms);
        count.store(count.load(mem_order) - 1, mem_order);
        //--count;
        std::string temp_str = "One customer out. Customers in queue = " + std::to_string(count.load(mem_order)) + "\n";
        std::cout << temp_str;
    }   
    
}

void enqueue3(std::atomic<int>& count, const int max_customers)
{
    int total_count = 0;
    while (total_count < max_customers)
    {
        count.store(count.load(std::memory_order_relaxed) + 1, std::memory_order_release);
       
        ++total_count;
        std::string temp_str = "One customer in. Customers in queue = " + std::to_string(count.load(std::memory_order_relaxed)) + ". Total customers = " + std::to_string(total_count) + "\n";
        std::cout << temp_str;
        std::this_thread::sleep_for(200ms);
    }

}

void dequeue3(std::atomic<int>& count)
{

    std::this_thread::sleep_for(10ms);
    while (count.load(std::memory_order_acquire)) // > 0)
    {
        std::this_thread::sleep_for(400ms);
        count.store(count.load(std::memory_order_acquire) - 1, std::memory_order_release);
        //--count;
        
        std::string temp_str = "One customer out. Customers in queue = " + std::to_string(count.load(std::memory_order_relaxed)) + "\n";
        std::cout <<  temp_str; 
    }



}