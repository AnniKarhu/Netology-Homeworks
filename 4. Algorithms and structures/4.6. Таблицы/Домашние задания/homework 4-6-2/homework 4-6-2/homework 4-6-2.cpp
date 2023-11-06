// homework 4-6-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

namespace new_namespace
{
    unsigned int real_string_hash(const std::string user_str, int p, int n); //Наивный хэш строки
    int get_user_number(); //ввод числа пользователем
}



int main()
{
    setlocale(LC_ALL, "rus");

    int user_p = 1;
    int user_n = 1;
    std::cout << "Введите p: ";
    user_p = new_namespace::get_user_number();
    std::cout << "Введите n: ";
    user_n = new_namespace::get_user_number();


    std::string user_string = "";
    do
    {
        std::cout << "Введите строку: ";
        std::cin >> user_string;
        std::cout << "Хэш строки " << user_string << " = " << new_namespace::real_string_hash(user_string, user_p, user_n) << "\n";
    } while (user_string != "exit");
}

 unsigned int new_namespace ::real_string_hash(const std::string user_str, int p, int n) //Наивный хэш строки
{
     if (n == 0)
     {
         return 0;
     }
     
    unsigned long long multiplier = 1;
    unsigned long long temp_result = 0;
    int str_len = user_str.length();
    for (int i = 0; i < str_len; ++i)
    {
        
        temp_result += char(user_str[i]) * multiplier;
        multiplier *= p;
    }

    return (temp_result % n);
}

int new_namespace::get_user_number() //ввод числа пользователем
{
    int num = 0;
    while (num <= 0)
    {
        std::cin >> num;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверное число. Попробуйте ввести другое. \n";
            num = 0;
        }
    }

    return num;
    
}