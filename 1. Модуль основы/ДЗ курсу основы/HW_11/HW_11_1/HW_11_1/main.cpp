#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
//#include <cstring>

int main()
{
	setlocale(LC_ALL, "Russian");

	char* chr_name = new char[100];
	char* chr_family = new char[100];

	std::cout << "Введите имя: ";
	std::cin >> chr_name;
	std::cout << "Введите фамилию: ";
	std::cin >> chr_family;

	int chr_size = strlen(chr_name) + strlen(chr_family) + strlen("Здравствуйте,  !") + 1;
	char* str = new char[chr_size];

	str = strcpy(str, "Здравствуйте, ");
	str = strcat(str, chr_name);
	str = strcat(str, " ");
	str = strcat(str, chr_family);
	str = strcat(str, "!");

	std::cout << str;


	delete[] chr_name;
	delete[] chr_family;
	delete[] str;

	return 0;
}