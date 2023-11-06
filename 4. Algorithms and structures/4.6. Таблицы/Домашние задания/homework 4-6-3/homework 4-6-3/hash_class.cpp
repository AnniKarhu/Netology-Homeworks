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


unsigned int hash_class::calculate_hash(const std::string& user_str)  //��� �� ������ ������
{
	return calculate_hash(user_str, 0, user_str.length() - 1);
}

unsigned int hash_class::calculate_hash(const std::string& user_str, const int start_index, int end_index) //��� �� ����� ������ �� ������� start_index �� end_index
{
	if (start_index > end_index)
	{
		return 0;
	}
	
	//unsigned long long multiplier = 1;
	unsigned long long temp_result = 0;

	//������ ���������� �������
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

unsigned int hash_class::hash_minus_first(const unsigned int old_hash, const std::string& new_str) //����� ����� ����
{
	unsigned int temp_hash = calculate_hash(new_str, 0, 0); //��� �� ������ �������
	
	//������� ��� ������� �������
	temp_hash = old_hash - temp_hash;
	
	//��������� ��� �� user_p
	//temp_hash /= user_p;
	
	return temp_hash;
}

unsigned int hash_class::hash_plus_end(const unsigned int old_hash, const std::string& new_str) //���� ����� ����
{
	//if (pos < 0)
	//{
	//	return 0;
	//}

	unsigned int temp_hash = calculate_hash(new_str, 0, 0); //��� �� ������ �������

	//��� ������� �� ������� �������
	/*if (pos == 0)
	{
		return temp_hash; //��������� ������ � �����. ���� ����� - ������� ������, ���������� ������.
	}
	else
	{
		temp_hash = temp_hash * pow(user_p, pos); 
		return (old_hash + temp_hash);
	}*/

	return (old_hash + temp_hash);

}