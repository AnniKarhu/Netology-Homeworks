#pragma once

class Test_class
{
public:
	Test_class()
	{
	
	}

	Test_class(int _x, int _y) : x{_x}, y {_y}
	{

	}

	~Test_class()
	{
	
	}

	int get_x()
	{
		return x;
	}

	int get_y()
	{
		return y;
	}

	void set_x(int value)
	{
		x = value;
	}

	void set_y(int value)
	{
		y = value;
	}


private:
	int x = 0;
	int y = 0;



};
