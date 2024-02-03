#include <string>
#include <algorithm>
#include "user_interface.h"

//������� ����
int main_menu()
{
	std::cout << "\n����� ���������� � ���� ������ � ��������. ������� ����� ������������� ��� ������ ����:\n";
	std::cout << "1. �������� ������ �������\n";
	std::cout << "2. �������� ������� ��� ������������� �������\n";
	std::cout << "3. �������� ������ � �������\n";
	std::cout << "4. ������� ������� � ������������� �������\n";
	std::cout << "5. ������� ������������� �������\n";
	std::cout << "6. ����� ������� �� ��� ������ � �����, �������, email ��� ��������\n\n";
	std::cout << "0. ��������� ������\n";

	int user_chr = -1;
	while (user_chr < 0)
	{
		std::cin >> user_chr;
		if (std::cin.fail())  //������ �����			
		{
			user_chr = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "��� ����� ���������. ����������, ������� ����� ������������� ��� ������ ����: ";
		}		
	}
	return user_chr;
}

//�������� ������ �������
void add_new_user(Data_base& db_unit)
{
	std::string UserName;
	std::string UserLastName; 
	std::string UserEmail;
	std::cin.get();	

	while (UserName.length() < 1)
	{
		std::cout << "������� ��� �������: ";	
		std::getline(std::cin, UserName);
	}
	
	while (UserLastName.length() < 1)
	{
		std::cout << "������� ������� �������: ";
		std::getline(std::cin, UserLastName);
	}
	
	while (UserEmail.length() < 1)
	{
		std::cout << "������� email �������: ";
		std::getline(std::cin, UserEmail);	
	}	

	try
	{
		if (db_unit.add_new_user(UserName, UserLastName, UserEmail))
		{
			std::cout << "����� ������ �������� � ���� ������ \n";
			//return true;
		}
		else
		{
			std::cout << "� ���������, ����� ������ �� ��������.\n";
			db_unit.print_last_error(); //������� ���������� � ��������� ������
			//return false;
		}
	}
	catch (...)
	{
		std::cout << "������ ��� ���������� ������� � ����" << "\n";
	}			
}

int get_search_param() //��������� � ������������, �� ������ ��������� ���� �������
{
	std::cout << "\n��� �������� � �������? \n";
	std::cout << "1. ���\n";
	std::cout << "2. �������\n";
	std::cout << "3. email\n";
	std::cout << "4. �������\n";
	std::cout << "0. ���-�� ��������, �� � �� ����, ��� ���\n";

	int user_chr = -1;
	while (user_chr < 0)
	{
		std::cin >> user_chr;
		if ((std::cin.fail()) ||  //������ �����	
			(user_chr < 0)||
			(user_chr > 4))
		{
			user_chr = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "��� ����� ���������. ����������, ������� ����� ������, �� �������� ����� ������ �������: ";
		}
	}
	return user_chr;
}

void print_user_info(Data_base& db_unit) //����� ���������� � �������
{
	//����� ������� ����������, ����� ������� ����� �������	
	int user_id = get_user_id(db_unit);

	//-1 - ������ � ���� �� �������
	if (user_id < 0)
	{
		std::cout << "� ���� ��� ���������� �� ����� ������� \n";
		return;
	}

	//�������� ���������� � ������� �� ��� id
	auto user_tuple = db_unit.get_user_by_id(user_id);
	std::string u_name = std::get<1>(user_tuple);
	std::string u_lastname = std::get<2>(user_tuple);
	std::string u_email = std::get<3>(user_tuple);

	std::cout << "������ ������: id = " << user_id << ", ��� =  " << u_name << ", ������� = " << u_lastname << ", email = " << u_email << "\n";
	
	//�������� ���������� � ��������� � ������� ������� ��������
	std::vector<std::string> phones_vector = db_unit.get_phones_list_by_user_id(user_id);

	if (phones_vector.empty())
	{
		std::cout << "������ ���������: �� �������\n";
	}
	else
	{
		for (const auto& elem : phones_vector)
			std::cout << elem << "\n";
	}
	
}

int get_user_id(Data_base& db_unit) //����� id �������
{	
	std::string user_info_str;
	std::map<int, std::tuple<std::string, std::string, std::string>> users_map;
	std::tuple<int, std::string, std::string, std::string> user_tuple;

	//�� ������ ��������� ����� ������
	int user_ch = get_search_param();
	switch (user_ch)
	{
	case 0: //�� ���� �����
		user_info_str = get_string("������� ������, ������� ������: "); //�������� ������ �� ������������
		users_map = db_unit.get_users_list_by_string(user_info_str); //������ ��������, ���������� ��������� ������ � �����-���� �� ����������
		break;
	
	case 1: //�� �����
		user_info_str = get_string("������� ��� �������: "); //�������� ��� �� ������������
		users_map = db_unit.get_users_list_by_name(user_info_str); //������ �������� � ��������� ������
		break;

	case 2:  //�� �������
		user_info_str = get_string("������� ������� �������: "); //�������� ������� �� ������������
		users_map = db_unit.get_users_list_by_lastname(user_info_str); //������ �������� � ��������� ��������
		break;

	case 3: //�� email
		user_info_str = get_string("������� email �������: "); //�������� email �� ������������
		users_map = db_unit.get_users_list_by_email(user_info_str); //������ �������� � ��������� email
		break;

	case 4:  //�� ������ ��������
		user_info_str = get_string("������� ������� �������: "); //�������� ������� �� ������������
		int usr_id = db_unit.get_user_id_by_phone(user_info_str); //������ � ��������� ���������
		return usr_id;

	}
	
	//�� ������� �� ����� ������
	if (users_map.size() == 0)
	{
		return -1;
	}
	
	//������� 1 ������
	if (users_map.size() == 1)
	{
		auto it = users_map.begin(); 
		return it->first;
	}

	//������� ��������� �������:
	std::cout << "\n� ���� ������� " << users_map.size() << " ���������� ���������: \n";
	
	auto it = users_map.begin();
	for (int i = 0;  it != users_map.end();  ++i, ++it)
	{
		int temp_id = it->first; 
		std::cout << i+1 << ": id = " << temp_id << ", "; 
		auto temp_tuple = users_map[temp_id];
		
		std::string temp_str = std::get<0>(temp_tuple); //���
		std::cout << "���:  " << temp_str << ", ";
		
		temp_str = std::get<1>(temp_tuple); //�������
		std::cout << "�������:  " << temp_str << ", ";

		temp_str = std::get<1>(temp_tuple); //email
		std::cout << "email:  " << temp_str << "\n";
	}

	std::cout << "������� ����� ������� ������� ��� 0, ���� �� �������� �� ���� �� �������������: \n";

	int user_chr = -1;
	while (user_chr < 0)
	{
		std::cin >> user_chr;
		if ((std::cin.fail()) || //������ �����	
			(user_chr < 0) ||
			(user_chr > users_map.size()))
		{
			user_chr = -1;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "������� ����� ������� ������� ��� 0, ���� �� �������� �� ���� �� �������������: \n ";
		}
	}
	
	//������������ ������, ��� �� �������� �� ���� �� ������������� ���������
	if (user_chr == 0)
	{
		return -1;
	}

	//����� ������ � ���� �� ������� ���������
	it = std::next(users_map.begin(), user_chr - 1);
	try
	{
		//�������� ����� it �� ������� ����
		return it->first;
	}
	catch (...)
	{
		return -1;
	}	
	
}

std::string get_string(std::string print_str) //�������� ������ �� ������������
{
	std::string user_str;

	std::cin.get();
	while (user_str.length() < 1)
	{
		std::cout << print_str;
		std::getline(std::cin, user_str);
	}

	return user_str;
}

void add_user_phone(Data_base& db_unit) //�������� ������� ������������� �������
{
	//������� ����� �������
	int user_id = get_user_id(db_unit);

	//-1 - ������ � ���� �� �������
	if (user_id < 0)
	{
		std::cout << "� ���� ��� ������ ������� \n";
		return;
	}

	//�������� ���������� � ������� �� ��� id
	auto user_tuple = db_unit.get_user_by_id(user_id);
	std::string u_name = std::get<1>(user_tuple);
	std::string u_lastname = std::get<2>(user_tuple);
	std::string u_email = std::get<3>(user_tuple);

	std::cout << "\n������ ������: id = " << user_id << ", ��� =  " << u_name << ", ������� = " << u_lastname << ", email = " << u_email << "\n";

	//�������� ���������� � ��������� � ������� ������� ��������
	std::vector<std::string> phones_vector = db_unit.get_phones_list_by_user_id(user_id);

	if (phones_vector.empty())
	{
		std::cout << "������ ���������: �� �������\n";
	}
	else
	{
		for (const auto& elem : phones_vector)
			std::cout << elem << "\n";
	}
	
	std::string user_str;
	do
	{		
		std::cout << "�������� ����� �������� ����� �������? \n 1 - �������� �����, \n 2 - �����\n";
		std::cin >> user_str;
	} while ((user_str != "1") && (user_str != "2"));
	
	if (user_str == "2")
	{
		return;
	}

	if (user_str == "1")
	{
		//�������� ������ �� ������������
		user_str = get_string("������� ����� ��������:\n"); //to-do �� ����������� ����� �������� �������� ���������� �� ������, ���������� �����, ������� � �.�. 
	}
	
	if (db_unit.add_user_phone(user_id, user_str))
	{
		std::cout << "������� ��������\n";
	}
	else
	{
		std::cout << "�� ������� �������� �������.\n";
		db_unit.print_last_error();
	}
}

void update_user_data(Data_base& db_unit) //�������� ������ � �������
{
	//������� ����� �������
	int user_id = get_user_id(db_unit);

	//-1 - ������ � ���� �� �������
	if (user_id < 0)
	{
		std::cout << "� ���� ��� ������ ������� \n";
		return;
	}

	//�������� ���������� � ������� �� ��� id
	auto user_tuple = db_unit.get_user_by_id(user_id);
	std::string u_name = std::get<1>(user_tuple);
	std::string u_lastname = std::get<2>(user_tuple);
	std::string u_email = std::get<3>(user_tuple);

	std::string u_name_new = u_name;
	std::string u_lastname_new = u_lastname;
	std::string u_email_new = u_email;

	std::string user_ch = "-1"; 
	while (user_ch != "0")
	{
		//����� ������ ������
		std::cout << "������ c id = " << user_id << ".  ����� ���������� � ������� ����� ��������?\n";
		
		std::cout << "1. ���:  ������� �������� = " << u_name;
		if (u_name == u_name_new) 	{std::cout << "\n";} 
		else { std::cout << "; ����� �������� = " << u_name_new << "\n"; }

		std::cout << "2. �������: ������� �������� = " << u_lastname; 
		if (u_lastname == u_lastname_new) { std::cout << "\n"; }
		else { std::cout << "; ����� �������� = " << u_lastname_new << "\n"; }

		std::cout << "3. email: ������� �������� = " << u_email; 
		if (u_email == u_email_new) { std::cout << "\n"; }
		else { std::cout << "; ����� �������� = " << u_email_new << "\n"; }

		std::cout << "0. ��� ������ �����. ��������� ���������� ����������.\n";

		do
		{
			std::cin >> user_ch;
		} while ((user_ch != "0") && (user_ch != "1") && (user_ch != "2") && (user_ch != "3"));
		
		if (user_ch == "0") { break; }
		
		//�������� ����� ��������		
		std::string new_value= get_string("������� ����� ��������: ");  

		if (user_ch == "1") u_name_new = new_value; //����� ���
		if (user_ch == "2") u_lastname_new = new_value; //����� ���
		if (user_ch == "3") u_email_new = new_value; //����� email

		user_ch = "-1";		
	}
	
	//���� �������� �� ��������, �����
	if ((u_name == u_name_new) && (u_lastname == u_lastname_new) && (u_email == u_email_new))
	{
		return;
	}
	else // ������ ����� �������� � ����
	{
		if (db_unit.update_user_data(user_id, u_name_new, u_lastname_new, u_email_new))
		{
			std::cout << "������ ������� ���������\n";
		}
		else
		{
			std::cout << "�� ������� �������� ������ �������.\n";
			db_unit.print_last_error();
		}
	}
}

void delete_user_phone(Data_base& db_unit) //������� ������� ������� 
{
	//������� ����� �������
	int user_id = get_user_id(db_unit);

	//-1 - ������ � ���� �� �������
	if (user_id < 0)
	{
		std::cout << "� ���� ��� ������ ������� \n";
		return;
	}

	//�������� ���������� � ������� �� ��� id
	auto user_tuple = db_unit.get_user_by_id(user_id);
	std::string u_name = std::get<1>(user_tuple);
	std::string u_lastname = std::get<2>(user_tuple);
	std::string u_email = std::get<3>(user_tuple);

	std::cout << "\n������ ������: id = " << user_id << ", ��� =  " << u_name << ", ������� = " << u_lastname << ", email = " << u_email << "\n";

	//�������� ���������� � ��������� � ������� ������� ��������
	std::vector<std::string> phones_vector = db_unit.get_phones_list_by_user_id(user_id);

	if (phones_vector.empty())
	{
		std::cout << "������ ���������: �� �������\n";
	}
	else
	{
		for (int i = 0; i < phones_vector.size(); i++)
		{
			std::cout << i + 1 << ". " << phones_vector[i] << "\n";
		}

		std::cout << "0. ������� ������ �������� �� �����. �����.\n";

		int user_ch = -1;
		do
		{
			std::cout << "������� ���������� ����� ��������, ������� ����� ������� ��� 0 ��� ������.";
			std::cin >> user_ch;
			if (std::cin.fail()) 
			{
				user_ch = -1;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');				
			}
		} while (user_ch < 0);

		if (user_ch == 0) return; //������������ ����� ������ �� �������
		if ((user_ch < 0) ||
			(user_ch >= phones_vector.size()))
		{
			std::cout << "���������� ������� �������������� �����. \n";
			return;
		}


		std::string  phone_to_delete = phones_vector[user_ch-1];

		std::cout << "�� �������, ��� ������ ������� ����� �������� " << phone_to_delete << "?\n";
		std::cout << "������� 1, ����� ����������� ��������: ";

		std::string user_str;
		std::cin >> user_str;

		if (user_str != "1") return;

		if (db_unit.delete_user_phone(user_id, phone_to_delete))
		{
			std::cout << "����� �������� " << phone_to_delete << " ������.\n";
		}
		else
		{
			std::cout << "�� ������� ������� ����� �������� " << phone_to_delete << ".\n";
			db_unit.print_last_error();
		}
	}
}

void delete_user(Data_base& db_unit) //������� ���������� � �������
{
	//������� ����� �������
	int user_id = get_user_id(db_unit);

	//-1 - ������ � ���� �� �������
	if (user_id < 0)
	{
		std::cout << "� ���� ��� ������ ������� \n";
		return;
	}

	//�������� ���������� � ������� �� ��� id
	auto user_tuple = db_unit.get_user_by_id(user_id);
	std::string u_name = std::get<1>(user_tuple);
	std::string u_lastname = std::get<2>(user_tuple);
	std::string u_email = std::get<3>(user_tuple);

	std::cout << "�� �������, ��� ������ ������� ��� ���������� � �������?\n";
	std::cout << "\n������: id = " << user_id << ", ��� =  " << u_name << ", ������� = " << u_lastname << ", email = " << u_email << "\n";
	std::cout << "������� 1, ����� ����������� ��������: ";

	std::string user_str;
	std::cin >> user_str;

	if (user_str != "1") return;

	if (db_unit.delete_user(user_id))
	{
		std::cout << "������ � ������� �������.\n";
	}
	else
	{
		std::cout << "�� ������� ������� ������ � �������.\n";
		db_unit.print_last_error();
	}





	

}
