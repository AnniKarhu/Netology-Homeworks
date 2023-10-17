// homework 4-2-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

//вычисление одного конкретного числа Фибоначчи - линейное по скорости O(n) выполнения и по памяти O(n).
//скорость - количество рекурсивных вызовов функции calculate_fib равно номеру числа 
//память - количество выделяемой памяти прямо пропорционально количеству вызовов - стек заполняется указателями на функцию + в каждой функции используются 
//входные переменные, значения которых копируются в каждую следующую функцию.

//напечатать ряд  чисел Фибоначчи - уже квадратичная асимптотика, так как для печати каждого числа оно вычисляется заново. Времени на выполнение - n*n/2.
//т.е. O(n*n) - не знаю, как тут в комментариях n в квадрате лучше написать. По памяти остается O(n)

#include <iostream>


unsigned long long  calculate_fibo(int num, int counter, unsigned long long fibo_0, unsigned long long  fibo_1);

int main()
{
    setlocale(LC_ALL, "rus");
    
    std::cout << "Введите количество чисел: ";
    int num = 0;
    std::cin >> num;

	while (std::cin.fail())
	{
		std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Введите количество чисел:  ";
		std::cin >> num;

	}

    int counter = 0;
    unsigned long long  fibo_0 = 0;
    unsigned long long  fibo_1 = 1;

    //вывести числа на экран
    for (int i = 0; i < num; ++i)
    {
         std::cout << calculate_fibo(i, counter, fibo_0, fibo_1) << "\n";

    }

    return 0;

}

unsigned long long  calculate_fibo(int num, int counter, unsigned long long  fibo_0, unsigned long long  fibo_1)
{
    if (num == counter)
    {
        return fibo_0;
    }
   
    ++counter;

    if (counter == num)
    {
        return fibo_1;
    }

    return (calculate_fibo(num, counter, fibo_1, fibo_0 + fibo_1));

}

