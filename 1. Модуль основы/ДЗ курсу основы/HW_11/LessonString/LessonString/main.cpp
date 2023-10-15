#define _CRT_SECURE_NO_WARNINGS  //эта строка нужна, чтобы отладчик не ругался на небезопасный код с функцией strcpy

#include <iostream>


int main()
{

	setlocale(LC_ALL, "Russian");
	/*char a = 'N';
	std::cout << static_cast<int> (a) << "\n";

	//****************************************************
	//копирование строк
	char arr[] = { "Welcom to the new world" };
	//*char destination[256];
	//*char destination[8];  //выход за пределы памяти - есть риск повредить другие данные программы - переменные или функции

	int StrLen = strlen(arr); //длина строки без учета нул-терминатора
	char* destination = new char[StrLen + 1]; //+1 , так как нужно учесть место под нул-терминатор


	int x = 10;
	int y = 20;
	int z = 30;

	std::cout << x << " \n";
	std::cout << y << " \n";
	std::cout << z << " \n";



	strcpy(destination, arr);

	std::cout << x << " \n";
	std::cout << y << " \n";
	std::cout << z << " \n";

	delete[] destination;*/


	//*********************************************
	//конкатенация
	/*char arr[] = { "Welcome to the new world!" };
	char arr2[] = {"Please follow me!"};

	char* destination = new char[strlen(arr) + strlen(arr2) + 1];

	//*destination = arr
	strcpy(destination, arr);

	//destination +=arr2
	strcat(destination, arr2); //сложение двух строк

	delete[] destination;*/


	//******************************************************
	//сравнение строк

	/*
	//strcmp(str1, str2) - возвращает 0, если строки равны, 1 или -1 если строки больше или меньше по алфавитному сравнению
	char arr[] = { "Welcome to the new world!" };
	char arr2[] = { "Please follow me!" };

	//if (arr == arr2) - так неверно

	if (strcmp(arr, arr2) == 0) //так верно или if (strcmp(arr, arr2) {std::cout << "NOT equal";}

	{
		std::cout << "equal";
	}
	else
	{
		std::cout << "NOT equal";
	}
	*/

	//**************************************
	/*
	//поиск символа 
	//strchr(arr, 'c') - возвращает указатель на символ в строке или nullptr, если нет символа в строке

	char arr[] = { "Welcome!" };
	char* d = strchr(arr, 'c');

	std::cout << d << "\n";

	*d = 'd';

	std::cout << d << "\n";
	std::cout << arr << "\n";

	arr[8] = '?';  //перезаписан нул-терминатор

	int x = 0; //переменная x хранится в той же автоматической памяти, что и строка
	//последующий вывод строки без нул терминатора дойдет до ближайшего 0 в памяти - либо это переменная x, либо другой случайный 0 - что раньше встретится

	std::cout << arr << "\n";

	//номер символа или плодстроки в строке - используем разность адресов
	int diff = d - arr;
	std::cout << diff << "\n";

	std::cout << (int *)(strchr(arr, 'R')); //nullptr выводится как 0

	*/


	//*****************************************
	//преобразование строки в число atoi, atol, atof. Возвращает 0 в случае неудачи

/*
	double x, x2, x3, x4;
	char str[] = "10.5";
	char str2[] = "10."; // = 10.0
	char str3[] = "1.5e5"; //= 1.5 * 10^5
	char str4[] = "1.5e-2"; //= 1.5 * 10^-2 = 1.5 * 0.01

	x = atof(str);
	x2 = atof(str2);
	x3 = atof(str3);
	x4 = atof(str4);

	std::cout << x << " " << x * 2 << "\n";
	std::cout << x2 << " " << x2 * 2 << "\n";
	std::cout << x3 << " " << x3 * 2 << "\n";
	std::cout << x4 << " " << x4 * 2 << "\n";

*/

//****************************************
//строки в стиле С++
//std::string - только в c++

//варианты объявлений:
char str0[] = { "Hello0" };
std::string str1 = {"Hello1"};
std::string str2{ "Hello2" };
std::string str3("Hello3");
std::string str4 = "Hello4";
std::string str5 = str4;
std::string str6 = str0;

//длина строки
std::cout << str1.length() << "\n";


//сложение строк

//std::string str = "Hello " + "world"; //так нельзя, хотя бы одна из правых частей должна быть типа std::string
//std::string str = std::string("Hello ") + "world"; //так можно
std::string str = static_cast<std::string>("Hello ") + "world"; //так можно

std::string s1 = "Hello ";
std::string s2 = s1 + "world"; 
std::string s3 = s1 + " " + "world";
//std::string s4 =  " " + "world" + s1; //так нельзя, так как первые две части в стиле си, а в си так складывать нельзя
std::string s4 = " " + s1 + "world"; //так можно

//стравнение двух строк
std::string string1 = "Hello";
std::string string2 = "Hello2";

if (string1 == string2)
{
	std::cout << "equal";
}

if (string1.compare(string2) == 0) //compare возвращает 0, если строки равны, -1 или 1 если не равны (сравнение по алфавиту)
{
	std::cout << "equal";
}

//поиск в строке - find - возвращает номер позиции или std::string::npos, если символ или подстрока не найдены
std::string str_find = "Hello";
std::cout << str_find.find('e') << "\n";
std::cout << str_find.find("lo") << "\n";
std::cout << (str_find.find("Hi") == std::string::npos) << "\n";

//std::string::npos имеет тип unsigned long long

unsigned long long x = str_find.find('l');
if (x != std::string::npos)
{
	std::cout << x << "\n";
}
else
{
	std::cout << "Not found " << "\n";
}

//преобразование строк в числа
//int std::stoi(std::string str)
//int std::stol(std::string str)
//int std::stof(std::string str) - float
//int std::stod(std::string str) - double

}







