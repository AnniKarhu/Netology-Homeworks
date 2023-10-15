/*Описание
Ваша задача — реализовать уже знакомую вам функцию swap (вспомнить можно здесь), но с помощью указателей, а не ссылок.

Обратите внимание, что в пространстве имён std уже есть функция swap. Поэтому НЕ используйте в своём решении конструкцию using namespace std;, так как в этом случае будет вызвана библиотечная функция swap, а не ваша.

Пример работы программы
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