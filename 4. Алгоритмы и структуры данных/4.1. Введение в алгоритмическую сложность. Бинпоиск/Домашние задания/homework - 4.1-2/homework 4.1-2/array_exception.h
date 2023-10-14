#pragma once

#include <iostream>
class ArrayException : public std::exception
{

public:
	ArrayException();	
	const char* what() const override;

};

