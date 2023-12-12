#include <iostream>
#include "vector_exception.h"

const char* Vector_Exception::what() const noexcept
{
	return "Выход за пределамы массива";
}
