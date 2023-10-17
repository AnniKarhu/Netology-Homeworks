// homework 4-2-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

//первоначальный вариант функции
unsigned long long  calculate_fibo(int num,  int counter = 0, unsigned long long  fibo_0 = 0, unsigned long long  fibo_1 = 1);

//функция может сразу печатать числа Фибоначчи в процессе вычисления - это избавит от необходимости использовать цикл и превратит алгоритм 
//по скорости в O(n)
unsigned long long  calculate_and_print_fibo_2(int num, bool print_fibo, std::string template_str, int counter = 0, unsigned long long  fibo_0 = 0, unsigned long long  fibo_1 = 1);

//измененный вариант - запомнить результаты вычислений в массиве
unsigned long long  calculate_fibo_3(unsigned long long* results_array, int num, int counter = 0, unsigned long long  fibo_0 = 0, unsigned long long  fibo_1 = 1);


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

  

   // int counter = 0;
  // unsigned int fibo_0 = 0;
  //  unsigned int fibo_1 = 1;

    //вывести числа на экран  с помощью цикла и первой функции
    std::cout << "Вариант 1 - Вызов в цикле рекурсивной функции calculate_fibo. Скорость O(n*n), память O(n)\n";
    for (int i = 0; i < num; ++i)
    {
        std::cout << calculate_fibo(i) << "\n";

    }

    //вывести числа на экран  с помощью второй функции calculate_and_print_fibo_2 - печать сразу при вычислении
    std::cout << "\n\n\nВариант 2 - с помощью второй функции - печать сразу при вычислении. Скорость O(n), память O(n)\n";
    std::cout << "\n Вычисленное число: " << calculate_and_print_fibo_2(num, true, "\n");
   

    //вывести числа на экран  с помощью третьей функции calculate_fibo_3 - сохранение результатов в массив
    unsigned long long* results_array = new unsigned long long[num] {};
    std::cout << "\n\n\nВариант 3 - с помощью третьей функции - вычисление и запись результатов в массив. Скорость O(n), память O(n)\n";
    std::cout << "\n Вычисленное число: " << calculate_fibo_3(results_array, num) << "\n";
    for (int i = 0; i < num; ++i)
    {
        std::cout << results_array[i] << "\n";
    }

   
    delete[] results_array;

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


unsigned long long  calculate_fibo_3(unsigned long long* results_array, int num, int counter, unsigned long long  fibo_0, unsigned long long  fibo_1)
{
    results_array[counter] = fibo_0;
    
    if (num == counter)
    {
        return fibo_0;
    }

    ++counter;

    if (counter == num)
    {
        return fibo_0;
    }

    return (calculate_fibo_3(results_array, num, counter, fibo_1, fibo_0 + fibo_1));
}

unsigned long long  calculate_and_print_fibo_2(int num, bool print_fibo, std::string template_str, int counter, unsigned long long  fibo_0, unsigned long long  fibo_1)
{
    if (print_fibo)
     {
            std::cout << fibo_0 << template_str;
     } 

    if (num == counter)
    {
        return fibo_0;
    }

    ++counter;

    if (counter == num)
    {
         return fibo_0;
    }

    return (calculate_and_print_fibo_2(num, print_fibo, template_str, counter, fibo_1, fibo_0 + fibo_1));
}