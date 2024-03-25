#include <iostream>
#include <thread>
#include <chrono>
#include <functional>

#include "thread_pool.h"

using namespace std::chrono_literals;

void func1()
{
    std::this_thread::sleep_for(200ms);
    std::cout << std::this_thread::get_id() << ": working " << __FUNCTION__ << "...\n";
}

void func2()
{
    std::this_thread::sleep_for(200ms);
    std::cout << std::this_thread::get_id() << ": working " << __FUNCTION__ << "...\n";
}

void addF1(thread_pool* thread_pool)
{
    if (thread_pool == nullptr) return;

    for (int i = 0; i < 5; ++i)
    {              
        std::this_thread::sleep_for(1s);
        thread_pool->submit(func1, "func1", i);
    }
}

void addF2(thread_pool* thread_pool)
{
    if (thread_pool == nullptr) return;

    for (int i = 5; i < 15; ++i)
    {
       
        std::this_thread::sleep_for(1s);
        thread_pool->submit(func2, "func2", i);
    }

    thread_pool->finish_tasks();
}


int main()
{
    
    thread_pool new_thread_pool;

    std::thread th1(addF1, &new_thread_pool);
    std::thread th2(addF2, &new_thread_pool);
   
    new_thread_pool.start_threads_work();

    th1.join();
    std::cout << "th1 finished\n";
    th2.join();
    std::cout << "th2 finished\n";

	return 0;
}