#pragma once
#include <iostream>

class hash_class
{
private:
	//int user_p = 9973;
	//int user_n = 1033;
public:
	hash_class();

	//void set_user_p(int new_user_p);
	//void set_user_n(int new_user_n);

	~hash_class();

	unsigned int calculate_hash(const std::string &user_str);  //хэш от полной строки
	unsigned int calculate_hash(const std::string &user_str, const int start_index, int end_index); //хэш от части строки от индекса start_index до end_index
	unsigned int hash_minus_first(const unsigned int old_hash, const std::string& new_str); //минус часть хэша
	unsigned int hash_plus_end(const unsigned int old_hash, const std::string& new_str); //плюс часть хэша

};
