
#include <iostream>
#include "array_exception.h"

const char* Array_Exception:: what() const noexcept 
{
	return "������� �������� � ������� �� ��������� ������� �������";
}
