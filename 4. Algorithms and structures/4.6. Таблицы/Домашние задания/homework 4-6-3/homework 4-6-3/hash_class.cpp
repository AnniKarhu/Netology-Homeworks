#include "hash_class.h"


hash_class::hash_class()
{

}

hash_class::~hash_class()
{

}


/*void hash_class::set_user_p(int new_user_p)
{
	if (new_user_p > 0)
	{
		user_p = new_user_p;
	}
}*/

/*void hash_class::set_user_n(int new_user_n)
{
	if (new_user_n > 0)
	{
		user_n = new_user_n;
	}
}*/


unsigned int hash_class::calculate_hash(const std::string& user_str)  //хэш от полной строки
{
	return calculate_hash(user_str, 0, user_str.length() - 1);
}

unsigned int hash_class::calculate_hash(const std::string& user_str, const int start_index, int end_index) //хэш от части строки от индекса start_index до end_index
{
	if (start_index > end_index)
	{
		return 0;
	}
	
	//unsigned long long multiplier = 1;
	unsigned long long temp_result = 0;

	//индекс последнего символа
	int str_len = user_str.length();	
	if (end_index >= str_len)
	{
		end_index = str_len - 1;
	}

	for (int i = start_index; i <= end_index; ++i)
	{

		//temp_result += char(user_str[i]) *multiplier;
		temp_result += char(user_str[i]);
		//multiplier *= user_p;
	}

	return temp_result;
	//return (temp_result % user_n);
}

unsigned int hash_class::hash_minus_first(const unsigned int old_hash, const std::string& new_str) //минус часть хэша
{
	unsigned int temp_hash = calculate_hash(new_str, 0, 0); //хэш от одного символа
	
	//вычесть хэш первого символа
	temp_hash = old_hash - temp_hash;
	
	//разделить все на user_p
	//temp_hash /= user_p;
	
	return temp_hash;
}

unsigned int hash_class::hash_plus_end(const unsigned int old_hash, const std::string& new_str) //плюс часть хэша
{
	//if (pos < 0)
	//{
	//	return 0;
	//}

	unsigned int temp_hash = calculate_hash(new_str, 0, 0); //хэш от одного символа

	//хэш зависит от позиции символа
	/*if (pos == 0)
	{
		return temp_hash; //добавляем всегда в конец. Если конец - нулевой индекс, складывать нечего.
	}
	else
	{
		temp_hash = temp_hash * pow(user_p, pos); 
		return (old_hash + temp_hash);
	}*/

	return (old_hash + temp_hash);

}