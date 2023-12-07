#include <iostream>
#include "table_exception.h"

const char* Table_Exception::what() const noexcept
{
	return "Использование неверного индекса двумерного массива";
}