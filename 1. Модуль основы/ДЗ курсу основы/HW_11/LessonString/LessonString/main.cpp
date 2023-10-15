#define _CRT_SECURE_NO_WARNINGS  //��� ������ �����, ����� �������� �� ������� �� ������������ ��� � �������� strcpy

#include <iostream>


int main()
{

	setlocale(LC_ALL, "Russian");
	/*char a = 'N';
	std::cout << static_cast<int> (a) << "\n";

	//****************************************************
	//����������� �����
	char arr[] = { "Welcom to the new world" };
	//*char destination[256];
	//*char destination[8];  //����� �� ������� ������ - ���� ���� ��������� ������ ������ ��������� - ���������� ��� �������

	int StrLen = strlen(arr); //����� ������ ��� ����� ���-�����������
	char* destination = new char[StrLen + 1]; //+1 , ��� ��� ����� ������ ����� ��� ���-����������


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
	//������������
	/*char arr[] = { "Welcome to the new world!" };
	char arr2[] = {"Please follow me!"};

	char* destination = new char[strlen(arr) + strlen(arr2) + 1];

	//*destination = arr
	strcpy(destination, arr);

	//destination +=arr2
	strcat(destination, arr2); //�������� ���� �����

	delete[] destination;*/


	//******************************************************
	//��������� �����

	/*
	//strcmp(str1, str2) - ���������� 0, ���� ������ �����, 1 ��� -1 ���� ������ ������ ��� ������ �� ����������� ���������
	char arr[] = { "Welcome to the new world!" };
	char arr2[] = { "Please follow me!" };

	//if (arr == arr2) - ��� �������

	if (strcmp(arr, arr2) == 0) //��� ����� ��� if (strcmp(arr, arr2) {std::cout << "NOT equal";}

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
	//����� ������� 
	//strchr(arr, 'c') - ���������� ��������� �� ������ � ������ ��� nullptr, ���� ��� ������� � ������

	char arr[] = { "Welcome!" };
	char* d = strchr(arr, 'c');

	std::cout << d << "\n";

	*d = 'd';

	std::cout << d << "\n";
	std::cout << arr << "\n";

	arr[8] = '?';  //����������� ���-����������

	int x = 0; //���������� x �������� � ��� �� �������������� ������, ��� � ������
	//����������� ����� ������ ��� ��� ����������� ������ �� ���������� 0 � ������ - ���� ��� ���������� x, ���� ������ ��������� 0 - ��� ������ ����������

	std::cout << arr << "\n";

	//����� ������� ��� ���������� � ������ - ���������� �������� �������
	int diff = d - arr;
	std::cout << diff << "\n";

	std::cout << (int *)(strchr(arr, 'R')); //nullptr ��������� ��� 0

	*/


	//*****************************************
	//�������������� ������ � ����� atoi, atol, atof. ���������� 0 � ������ �������

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
//������ � ����� �++
//std::string - ������ � c++

//�������� ����������:
char str0[] = { "Hello0" };
std::string str1 = {"Hello1"};
std::string str2{ "Hello2" };
std::string str3("Hello3");
std::string str4 = "Hello4";
std::string str5 = str4;
std::string str6 = str0;

//����� ������
std::cout << str1.length() << "\n";


//�������� �����

//std::string str = "Hello " + "world"; //��� ������, ���� �� ���� �� ������ ������ ������ ���� ���� std::string
//std::string str = std::string("Hello ") + "world"; //��� �����
std::string str = static_cast<std::string>("Hello ") + "world"; //��� �����

std::string s1 = "Hello ";
std::string s2 = s1 + "world"; 
std::string s3 = s1 + " " + "world";
//std::string s4 =  " " + "world" + s1; //��� ������, ��� ��� ������ ��� ����� � ����� ��, � � �� ��� ���������� ������
std::string s4 = " " + s1 + "world"; //��� �����

//���������� ���� �����
std::string string1 = "Hello";
std::string string2 = "Hello2";

if (string1 == string2)
{
	std::cout << "equal";
}

if (string1.compare(string2) == 0) //compare ���������� 0, ���� ������ �����, -1 ��� 1 ���� �� ����� (��������� �� ��������)
{
	std::cout << "equal";
}

//����� � ������ - find - ���������� ����� ������� ��� std::string::npos, ���� ������ ��� ��������� �� �������
std::string str_find = "Hello";
std::cout << str_find.find('e') << "\n";
std::cout << str_find.find("lo") << "\n";
std::cout << (str_find.find("Hi") == std::string::npos) << "\n";

//std::string::npos ����� ��� unsigned long long

unsigned long long x = str_find.find('l');
if (x != std::string::npos)
{
	std::cout << x << "\n";
}
else
{
	std::cout << "Not found " << "\n";
}

//�������������� ����� � �����
//int std::stoi(std::string str)
//int std::stol(std::string str)
//int std::stof(std::string str) - float
//int std::stod(std::string str) - double

}







