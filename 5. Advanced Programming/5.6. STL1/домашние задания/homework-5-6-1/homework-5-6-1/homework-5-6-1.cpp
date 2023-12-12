// homework-5-6-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main()
{
    setlocale(LC_ALL, "Russian");

	std::string temp_str; 
    std::ifstream fin("in_data.txt"); 	//файл с текстом


	if (!(fin.is_open()))
	{
		std::cout << "Файл не существует";
		return 0;
	}

	std::map<char, int> new_map{};	//контейнер хранит уникальные значения - ключ - символ, значение - счетчик количества этих символов

	while (!(fin.eof()))
	{		
		std::getline(fin, temp_str);
	    for (int i = 0; i < temp_str.length(); ++i)
		{
			char chr = temp_str[i];
			//если символ уже есть, его счетчик увеличивается на 1
			//если символа еще нет - он вставляется сразу с увеличением счетчика до 1
			++new_map[chr]; //есть ли гарантия, что в пустом элементе значение по умолчанию 0?
		}		
	}

	for (const auto& elem : new_map)
		std::cout << elem.first << ": " << elem.second << std::endl;

	fin.close();
	return 0;
}

