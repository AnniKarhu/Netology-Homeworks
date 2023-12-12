#pragma once

#include <iostream>

class Vector_Exception : public std::exception
{
public:
	const char* what() const noexcept override;
};