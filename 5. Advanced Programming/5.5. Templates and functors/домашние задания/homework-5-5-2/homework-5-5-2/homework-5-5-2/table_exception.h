#pragma once
#include <iostream>
class Table_Exception : public std::exception
{
public:
	const char* what() const noexcept override;
};