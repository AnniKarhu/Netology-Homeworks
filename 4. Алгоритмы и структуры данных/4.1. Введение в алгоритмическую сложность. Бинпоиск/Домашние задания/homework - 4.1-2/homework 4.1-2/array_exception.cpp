#include <iostream>
#include "array_exception.h"


ArrayException::ArrayException()
	{

	}


const char* ArrayException::what() const
{
	return "������ ������� ������� - ������ < 0. ";
}

