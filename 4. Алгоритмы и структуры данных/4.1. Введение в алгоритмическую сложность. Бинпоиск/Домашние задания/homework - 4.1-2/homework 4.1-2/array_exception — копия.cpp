#include <iostream>
#include "array_exception.h"


ArrayException::ArrayException()
	{

	}


const char* ArrayException::what() const
{
	return "ќшибка индекса массива - индекс < 0."; //почему этот текст отображаетс€ кракоз€брами
}

