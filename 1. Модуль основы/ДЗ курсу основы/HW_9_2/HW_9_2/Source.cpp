/*��������
���� ������ � ����������� ��� �������� ��� ������� swap (��������� ����� �����), �� � ������� ����������, � �� ������.

�������� ��������, ��� � ������������ ��� std ��� ���� ������� swap. ������� �� ����������� � ���� ������� ����������� using namespace std;, ��� ��� � ���� ������ ����� ������� ������������ ������� swap, � �� ����.

������ ������ ���������
a = 5, b = 8
a = 8, b = 5
*/


#include <iostream>

void swap(int* a, int* b);

int main() {
	int a = 5, b = 8;
	int* ptr_a = &a;
	int* ptr_b = &b;

	std::cout << "a = " << a << ", b = " << b << std::endl;

	swap(ptr_a, ptr_b);

	std::cout << "a = " << a << ", b = " << b << std::endl;

	return 0;
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}