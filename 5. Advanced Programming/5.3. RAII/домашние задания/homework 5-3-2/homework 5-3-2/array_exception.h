#pragma once

#include <iostream>

class Array_Exception : public std::exception
{
public:
	const char* what() const noexcept override;	
};