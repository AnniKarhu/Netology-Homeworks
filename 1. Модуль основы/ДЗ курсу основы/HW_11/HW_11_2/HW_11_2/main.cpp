//#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int main()
{
	setlocale(LC_ALL, "Russian");
	
	
	char chr_word[] = {"hello"};
	std::string new_word = "";

	
	
	while ( new_word != chr_word)
	{
		
		std::cout << "chr_word = " << chr_word << "\n";
		std::cout << "new_word = " << new_word << "\n";
		std::cout << "Угадайте слово: ";
		std::cin >> new_word;

		if (new_word != chr_word)
		{
			std::cout << "Неправильно" << "\n";
			std::cout << "chr_word2 = " << chr_word << "\n";
			std::cout << "new_word2 = " << new_word << "\n";
		}
	}

	std::string win_str = "Правильно! Вы победили! Загаданное слово — ";
	win_str = win_str + chr_word;
	std::cout << win_str;
	
	
	
	return 0;
}

