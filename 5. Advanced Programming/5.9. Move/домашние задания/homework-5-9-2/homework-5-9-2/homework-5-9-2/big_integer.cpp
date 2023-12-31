#include <iostream>
#include <string>
#include <math.h>

#include "big_integer.h"

big_integer::big_integer(std::string value_str)
{
	//std::cout << "обычный конструктор \n";
	big_vector = new std::vector<int>;
		
	if (value_str.size() == 0)
	{
		delete big_vector;
		big_vector = nullptr;
		return;
	}
	
	//знаком минус может быть только первый элемент
	int start_index = 0;
	
	if (value_str[0] == '-')
	{
		start_index = 1;
		sign = -1;
	}	

	std::string temp_str = "";
	for (int i = value_str.size() - 1, j = 1; i >= start_index && j <= elem_size; --i, ++j)
	{
		//проверка на знак минус нужна здесь, так как знак минус в начале группы не вызовет исключения
		if (value_str[i] == '-')
		{
			delete big_vector;
			big_vector = nullptr;
			return;
		}
		
		temp_str = value_str[i] + temp_str;
		
		if ((j == elem_size) ||			//конец группы разрядов
			(i == start_index))  //или конец строки
		{
			try
			{
				int temp_int = std::stoi(temp_str); //to do - убрать лишнюю строку
				(*big_vector).push_back(temp_int);
				//std::cout << "> " << temp_str << "\n";
			}
			catch (...)
			{
				delete big_vector;
				big_vector = nullptr;
				break;
			}

			j = 0;
			temp_str = "";
		}			
	}

}

big_integer::big_integer(const big_integer& other)  //конструктор копирования
{
	//std::cout << "конструктор копирования\n";
	
	sign = other.sign;
	
	if (other.big_vector != nullptr)
	{
		big_vector = new std::vector<int>;
		for (int i = 0; i < other.get_size(); ++i)
		{
			big_vector->push_back(other.big_vector->at(i));
		}

	}
	
}



big_integer::big_integer(big_integer&& other)	// конструктор перемещения
{
	//std::cout << "конструктор  перемещения\n";

	big_vector = other.big_vector;
	sign = other.sign;
	
	other.big_vector = nullptr;
}

big_integer::~big_integer()
{
	//std::cout << "деструктор\n";
	delete big_vector;
}

big_integer& big_integer::operator=(const big_integer& other) //оператор присваивания
{
	//std::cout << "оператор присваивания \n";

	if (this != &other) //нет смысла присваивать объект самому себе
	{
		return *this = big_integer(other);

	}

	return *this;
}

big_integer& big_integer::operator=(big_integer&& other)       // оператор перемещающего присваивания
{
	//std::cout << "оператор перемещающего присваивания\n";
	return *this = big_integer(other);
}

big_integer big_integer::operator+(const big_integer& other) //оператор сложения
{
	//std::cout << "оператор сложения\n";

	big_integer temp_sum_big_integer("");
	
	if ((!this->value_is_valid()) || (!other.value_is_valid()))
	{
		//нельзя складывать невалидные значение - вернуть результат - тоже невалидное значение
		return temp_sum_big_integer;
	}

	temp_sum_big_integer.big_vector = new std::vector<int>;
	int limit = pow(10, elem_size);

	//сколько элементов хранит вектор каждого из больших чисел
	int size_1 = 0;
	int size_2 = 0;
	
	size_1 = this->get_size();
	size_2 = other.get_size(); 	 
	
	int exceed_sum = 0;
	int i = 0;

	while ((i < size_1) || (i < size_2)) //перебрать элементы обоих массивов
	{
		int sum_1 = 0;
		int sum_2 = 0;

		if (i < size_1)  //получить элемент первого числа
		{
			sum_1 = this->big_vector->at(i); // *this->sign;
		}

		if (i < size_2)  //получить элемент второго числа
		{
			sum_2 = other.big_vector->at(i); // *other.sign
		}

		if (((this->sign < 0) && (other.sign < 0)) ||  //оба числа отрицательные 
			((this->sign > 0) && (other.sign > 0)))   //или оба числа положительные
		{
			int temp_sum = abs(sum_1 + sum_2 + exceed_sum);

			//добавить в новый объект сумму слагаемых и перенесенный кусочек от предыдущего сложения
			temp_sum %= limit;
			temp_sum_big_integer.big_vector->push_back(temp_sum);
			exceed_sum = (sum_1 + sum_2 + exceed_sum) / limit;
			
			//если есть кусочек от предыдущего сложения, его тоже нужно добавить
			if (exceed_sum > 0)
			{
				temp_sum_big_integer.big_vector->push_back(abs(exceed_sum));
			}

		}
		else  //одно из чисел отрицательное
		{
			//определить уменьшаемое и вычитаемое
			int reduced = 0;
			int	subtracted = 0;
			int temp_exceed_sum = 0;

			if (module_greater(*this, other))//уменьшаемое то, которое больше по молулю
			{
				reduced = sum_1;   //уменьшаемое
				subtracted = sum_2; //вычитаемое
			}
			else
			{
				reduced = sum_2;   //уменьшаемое
				subtracted = sum_1; //вычитаемое
			}
			
			if ((reduced - exceed_sum) < subtracted) //вычитаем по одному элементу - если уменьшаемое меньше вычитаемого, забрать один разряд из следующего элемента
			{
				reduced += limit; //приписать единицу слева
				temp_exceed_sum = 1;  //вычесть единицу из следующего элемента 
			}

			int temp_sum = reduced - subtracted - exceed_sum;
			temp_sum_big_integer.big_vector->push_back(temp_sum);

			exceed_sum = temp_exceed_sum;
		}
		++i;		
	}		
	
	//определить знак результата
	if ((this->sign + other.sign) < 0) //если оба знака минус, результат тоже минус
	{
		temp_sum_big_integer.sign = -1;
	}
	else if ((this->sign + other.sign) > 0) //если оба знака плюс, результат тоже плюс
	{
		temp_sum_big_integer.sign = 1;
	}
	else //знаки слагаемых разные
	{
		//если большее по модулю число отрицательное
		if ((module_greater(*this, other) && (this->sign < 0)) ||
			(module_greater(other, *this)) && (other.sign < 0))
		{
			temp_sum_big_integer.sign = -1;
		}
		else
		{
			temp_sum_big_integer.sign = 1;
		}
	}
	
	//почистить лишние разряды слева - все, равное 0
	while (temp_sum_big_integer.big_vector->back() == 0)
	{
		std::vector<int>::iterator it = temp_sum_big_integer.big_vector->end() - 1;
		temp_sum_big_integer.big_vector->erase(it);
	}

	return temp_sum_big_integer; 
}

big_integer big_integer::operator-(const big_integer& other) //оператор вычитания
{
	//std::cout << "оператор вычитания\n";
	big_integer temp_other(other);
	temp_other.sign *= -1;
	return *this + temp_other;
}


big_integer big_integer::operator*(const int& other) //оператор умножения
{
	
	//std::cout << "оператор умножения\n";

	big_integer temp_mult_big_integer("");

	if (!this->value_is_valid()) 
	{
		//нельзя умножать невалидные значение - вернуть результат - тоже невалидное значение
		return temp_mult_big_integer;
	}

	temp_mult_big_integer.big_vector = new std::vector<int>;
	int limit = pow(10, elem_size);

	int temp_sign = 1;
	int mult = other;

	if (other < 0)
	{
		temp_sign = -1;
		mult *= -1;
	}

	temp_sign *= this->sign;
	int exceed_value = 0;
	for (int i = 0; i < this->get_size(); ++i) //перемножить каждый элемент
	{
		
		int temp_value = big_vector->at(i) * mult;
		temp_value += exceed_value;
		
		exceed_value = temp_value / limit;

		temp_mult_big_integer.big_vector->push_back(temp_value % limit);
	}

	if (exceed_value > 0)
	{
		temp_mult_big_integer.big_vector->push_back(exceed_value);
	}
		
	//почистить лишние разряды слева - все, равное 0
	while (temp_mult_big_integer.big_vector->back() == 0)
	{
		std::vector<int>::iterator it = temp_mult_big_integer.big_vector->end() - 1;
		temp_mult_big_integer.big_vector->erase(it);
	}

	temp_mult_big_integer.sign = temp_sign;

	return temp_mult_big_integer;
}

bool big_integer::module_greater(const big_integer& first, const big_integer& second) //сравнение чисел по модулю
{
	if ((!first.value_is_valid()) || (!second.value_is_valid())) //нельзя сравнивать невалидные числа
	{
		return false;
	}
	
	if (first.get_size() > second.get_size()) //это число имеет больше разрядов, чем other
	{
		return true;
	}
	else if (first.get_size() < second.get_size()) //это число имеет меньше разрядов, чем other
	{
		return false;
	}
	else //количество разрядов (и элементов) равно
	{
		return first.big_vector->back() > second.big_vector->back(); //нужно сравнить старшие разряды (элементы)
	}
}

bool big_integer::value_is_valid() const // = true; //поле принимает значение false, если число не валидно
{
	if ((this->big_vector == nullptr) ||
		(this->big_vector->size() == 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

int big_integer::get_size() const
{
	if ((big_vector == nullptr) ||
		(!value_is_valid()))
		return 0;

	return (*big_vector).size();
}

//std::string big_integer::get_elements()
//{
//	if (!value_is_valid())
//	{
//		return "invalid";
//	}
//	
//	std::string temp_str = "";
//
//	for (int i = 0; i < big_vector->size(); ++i)
//	{
//		std::cout << "big_vector[" << i << "] = " << (*big_vector)[i] << "\n";
//	}
//
//	for (const auto& elem : *big_vector)
//	{
//		temp_str += std::to_string(elem) + " ";
//	}
//
//	return temp_str;
//}


//вывод большого числа
std::ostream& operator<<(std::ostream& os, const big_integer& my_big_int)
{
	if ((my_big_int.big_vector == nullptr) ||
		(!my_big_int.value_is_valid()))
	{
		std::string str = "invalid_value";
		return os << "value = " << str;
	}
		
	std::string final_str = "";

	for (int i= my_big_int.big_vector->size() - 1; i >=0; --i )
	{
		std::string temp_str = std::to_string(my_big_int.big_vector->at(i));		

		//дополнить нулями до блока
		if (i != my_big_int.big_vector->size() - 1)  //кроме старшего разряда
		{
			int temp = my_big_int.elem_size - temp_str.size();
			while (temp_str.size() <= temp)
			{
				temp_str = "0" + temp_str;
			}
		}		

		final_str += temp_str;		
	}

	if (my_big_int.sign < 0)
	{
		final_str = "-" + final_str;
	}

	//return os << "value = " << final_str; 
	return os  << final_str;
}