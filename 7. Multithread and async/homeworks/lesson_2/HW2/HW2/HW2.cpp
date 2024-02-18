
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <Windows.h>
#include <random>

std::mutex m;

std::atomic<bool> start_treads = false;     //флаг старта потоков 

class RandomException : public std::exception
{
public:
    const char* what() const override { return "Random exception"; }
};

bool try_number(int number, int max_calc);

void thread_calculation(int thr_num, const int calc_len);

int main()
{
    //system("cls");
    int thread_num = 20; //количество потоков
    const int calculation_length = 50; //количество вычислений в каждом из потоков
    std::vector<std::thread> threads_vector;    //массив потоков
    
    for (int i = 0; i < thread_num; ++i)
    {
        threads_vector.push_back(std::thread(thread_calculation, i, calculation_length));
    }

    start_treads = true;

    for (int i = 0; i < thread_num; ++i)
    {
        threads_vector[i].join();
    }

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord;
    coord.X = 0;
    coord.Y = thread_num + 1;

    SetConsoleCursorPosition(console, coord);

    std::cout << "End\n";
    return 0;
}

bool try_number(int number, int max_calc)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, max_calc);

    if (dist(gen) == number)
    {
        throw RandomException();
    }

    return true;
}

void thread_calculation(int thr_num, const int calc_len)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord;
    coord.X = 0;
    coord.Y = thr_num;

    //вывести идентификатор потока
    std::unique_lock<std::mutex> lk(m);
    SetConsoleCursorPosition(console, coord);
    std::cout << thr_num << " " << std::this_thread::get_id() << ":\t";
    lk.unlock();

    while (!start_treads) //подождать готовность остальных потоков
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < calc_len; ++i)
    {
        lk.lock();
        coord.X = 10 + i;
        SetConsoleCursorPosition(console, coord);
        try
        {
            if (try_number(i, calc_len))
            {
                std::cout << char(219);
            }
        }
        catch (...)
        {
            SetConsoleTextAttribute(console, FOREGROUND_RED);
            std::cout << char(219);
            SetConsoleTextAttribute(console, FOREGROUND_INTENSITY);
        }


        lk.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    //вывести время работы
    lk.lock();
    coord.X = 10 + calc_len;
    SetConsoleCursorPosition(console, coord);
    std::cout << "\t" << elapsed_seconds.count() << "s\t";
    lk.unlock();

}