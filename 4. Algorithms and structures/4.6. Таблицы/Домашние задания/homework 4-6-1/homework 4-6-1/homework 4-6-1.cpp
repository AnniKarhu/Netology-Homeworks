// homework 4-6-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

unsigned int simple_string_hash(const std::string user_str); //Наивный хэш строки

int main()
{
    setlocale(LC_ALL, "rus");

    std::string user_string = "";
    do
    {
        std::cout << "Введите строку: ";
        std::cin >> user_string;
        std::cout << "Наивный хэш строки " << user_string << " = " << simple_string_hash(user_string) << "\n";
    } while (user_string != "exit");
}

unsigned int simple_string_hash(const std::string user_str) //Наивный хэш строки
{
  
    unsigned int result = 0;
    int str_len = user_str.length();
    for (int i = 0; i < str_len; ++i)
    {
      //  std::cout << user_str[i] << " >> code = " << char(user_str[i]) << "\n";
        result += char(user_str[i]);
    }

    return result;
}