// homework 4-6-3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <Windows.h>

#include "hash_class.h"   
    
std::string get_string(int max_str_len); //ввод строки длиной не больше max_str_len. Если max_str_len = 0, ограничения нет.
int find_substring_light_rabin_karp(const std::string& user_str, const std::string& user_substr, hash_class* new_hash_class); //поиск подстроки user_substr в строке  user_str

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    hash_class new_hash_class;
    
    std::string user_string = "";
    std::cout << "Введите строку, в которой будет осуществляться поиск: ";
    std::cin >> user_string; //ввод строки

    std::string user_substring = "";
    do
    {  
        std::cout << "Введите подстроку, которую нужно найти: ";
        user_substring = get_string(user_string.length()); //ввод подстроки

        int str_pos = find_substring_light_rabin_karp(user_string, user_substring, &new_hash_class);
        if (str_pos < 0)
        {
            std::cout << "Подстрока " << user_substring << " не найдена\n";
        }
        else
        {
            std::cout << "Подстрока " << user_substring << " найдена по индексу " << str_pos << "\n";
        }
        
    } while (user_substring != "exit");
}


std::string get_string(const int max_str_len) //ввод строки длиной не больше max_str_len. Если max_str_len = 0, ограничения нет.
{
    while (1)
    {
        std::string user_str = "";
        std::cin >> user_str;
        if ((max_str_len == 0) ||
            (user_str.length() <= max_str_len))
        {
            return user_str;
        }
        std::cout << "Подстрока не может быть длиннее строки. Попробуйте еще раз. \n";
    }
}

int find_substring_light_rabin_karp(const std::string &user_str, const std::string &user_substr,  hash_class* new_hash_class) //поиск подстроки user_substr в строке  user_str
{
    unsigned int substr_hash = new_hash_class->calculate_hash(user_substr); // real_string_hash(user_substr, 0, user_substr.length()-1); //хэш подстроки
    int substr_len = user_substr.length(); 
    int str_len = user_str.length();
   
    unsigned int part_hash = new_hash_class->calculate_hash(user_str, 0, user_substr.length() - 1);  // real_string_hash(user_str, 0, user_substr.length() - 1); //хэш начальной части строки

    int i = 0; //счетчик цикла
    do
    {        
        if (substr_hash == part_hash) //хэши совпали, есть вероятность совпадения подстрок
        {
            //проверить посимвольно
            bool temp_res = true;
            for (int j = 0; j < substr_len; ++j)
            {
                if (user_str[i + j] != user_substr[j]) //если не совпал хоть один символ
                {
                    temp_res = false; //строки не совпадают
                    break; //дальнейшая проверка этого куска бессмысленна
                }
            }

            if (temp_res) //если после цикла temp_res = true
            {
                return i;//строки совпали, можно вернуть позицию
            }
        }
        else //хэши не совпали
        {
            //пересчитать хэш для следующего куска строки
            part_hash = new_hash_class->hash_minus_first(part_hash, &user_str[i]); //вычесть хэш первого символа
            part_hash = new_hash_class->hash_plus_end(part_hash, &user_str[i + substr_len]);//добавить хэш следующего в очереди символа

        }

        ++i; //перейти к следующему индексу строки
    } while (i <= (str_len - substr_len));

    return -1;
}