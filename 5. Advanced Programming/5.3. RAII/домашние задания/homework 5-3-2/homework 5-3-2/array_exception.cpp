
#include <iostream>
#include "array_exception.h"

const char* Array_Exception:: what() const noexcept 
{
	return "Попытка работать с памятью за пределами размера массива";
}
