#pragma once

template<class T>
class my_unique_ptr
{
public:
	my_unique_ptr(T* _raw_ptr): raw_ptr{ _raw_ptr }
	{
				
	}

	my_unique_ptr(const my_unique_ptr&) = delete; //запретить конструктор копирования
	my_unique_ptr& operator=(const my_unique_ptr&) = delete; //запретить оператор присваивания

	~my_unique_ptr()
	{
		delete raw_ptr;
	}

	T operator *()
	{
		return *raw_ptr;
	}

	T* operator->()
	{
		//return raw_ptr;
		return this;
	}



private:
	T* raw_ptr = nullptr;

};