// HW2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>
#include <chrono>

std::once_flag flag;
using namespace std::chrono_literals;

void test_func(std::vector<int>& vec_1, std::vector<int>& vec_2, int limit_min, int limit_max, std::vector<int>& vec_res);

int main()
{
    setlocale(LC_ALL, "rus");

    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << "\n";
    std::cout << "\t\t10\t\t100\t\t1000\t\t10000\t\t100000\t\t1000000\n";
    
    int threads_count = 1;
    const int start_vector_size = 10;
    const int max_vector_size = 1000000;
    int vector_size = start_vector_size;

    std::vector<int> vector_1;
    std::vector<int> vector_2;
    std::vector<int> vector_result;
    std::vector<std::thread> threads_vector; 

    while (threads_count <= 16)
    {
      std::cout << "\n" << threads_count << " потоков: \t";        
      while (vector_size <= max_vector_size)
      {
        for (int i = 0; i < vector_size; ++i)
        {
            vector_1.push_back(i);
            vector_2.push_back(i);
        }

        int limit_min = 0;
        int limit_max = 0;
        int limit_increment = vector_size / threads_count;
        bool plus_one = vector_size % threads_count;

        
        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < threads_count; ++i)
        {
            limit_max = limit_min + limit_increment - 1;

            if (vector_size % threads_count > 0)
                if (plus_one)
                {
                    limit_max++;
                    plus_one = false;
                }
                else
                {
                    plus_one = true;
                }

            if (limit_max >= vector_size)
            {
                limit_max = vector_size - 1;
            }


            if (limit_min < vector_size)
            {
                //  std::cout << i << ": limit_min = " << limit_min << "; limit_max = " << limit_max << "\n";
                int instr_count = limit_max - limit_min + 1;
                //  std::cout << "Операций для потока: " << instr_count << "\n";
                  // test_func(vector_1, vector_2, limit_min, limit_max, vector_result);
                if (instr_count > 0)
                {
                    threads_vector.push_back(std::thread(test_func, std::ref(vector_1), std::ref(vector_2), limit_min, limit_max, std::ref(vector_result)));
                }

                limit_min = limit_max + 1;
            }
            else
                break;
        }

        for (int i = 0; i < threads_vector.size(); ++i)
        {
            if (threads_vector[i].joinable())
            {
                threads_vector[i].join();
                //  std::cout << "Поток завершен join " << i << " \n";

            }
            //else
            //{
            //    std::cout << "Поток не joinable " << i << " \n";
            //}

        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << elapsed_seconds.count() << "s\t";

        vector_1.clear();
        vector_2.clear();
        vector_result.clear();
        threads_vector.clear();
        vector_size *= 10;
      }
      vector_size = start_vector_size;
        threads_count *= 2;    

    }
    
}

void test_func(std::vector<int>& vec_1, std::vector<int>& vec_2, int limit_min, int limit_max, std::vector<int>& vec_res)
{
  //  std::call_once(flag, []() {  
  //      std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << "\n";  
  //      std::cout << "\t\t10\t\t100\t\t1000\t\t10000\t\t100000\t\t1000000\n1 поток:\t";
  //      });
   
    
    for (int i = limit_min; i <= limit_max; ++i)
    { 
        vec_res.push_back(vec_1[i] + vec_2[i]);
    }

}
    
