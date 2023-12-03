
#include "Factorial.h"

unsigned int Factorial(unsigned int number) {
	if (number == 0 || number == 1)
		return 1;
	else
		return Factorial(number - 1) * number;
}