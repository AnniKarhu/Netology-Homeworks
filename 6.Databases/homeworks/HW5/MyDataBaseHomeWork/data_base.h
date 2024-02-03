#pragma once
#include <iostream>
#include <pqxx/pqxx> 

class Data_base
{
private:
	const std::string connection_str; //������ ���������� ��� �����������
	pqxx::connection* connection_ptr = NULL;
	std::string last_error; //�������� ��������� ��������� ������
	bool connect_db(); //��������� ����������� � ��
	bool create_tables(); //������� ����������� �������
	bool create_templates(); //������� ������� ��� ������

public:

	explicit Data_base(const std::string params_str)  noexcept;
	
	bool start_db(); //������ ������ � ����� ������
	std::string get_last_error_desc(); //�������� �������� ��������� ��������� ������
	void print_last_error(); //������� ���������� � ��������� ������

	void test_insert(); //������ ����� �������

	Data_base(const Data_base& other) = delete; //����������� �����������
	Data_base(Data_base&& other) noexcept;	// ����������� �����������
	Data_base& operator=(const Data_base& other) = delete;  //�������� ������������ 
	Data_base& operator=(Data_base&& other) noexcept;       // �������� ������������� ������������
	~Data_base();	

	/*�������������� ������������ � ����� ������*/	

	/*���������� � �������*/

	//�������� ���������� � ������� �� ��� id	
	std::tuple<int, std::string, std::string, std::string> get_user_by_id(int UserId); 
	
	//�������� ������ ������� ��������� �� id �������
	std::vector<std::string> get_phones_list_by_user_id(int UserId); 
	
	//����� �������� �� ������������ ������ - ���, �������, email, �������	
	std::map<int, std::tuple<std::string, std::string, std::string>> get_users_list_by_string(std::string DefaultStr);
	
	//����� �������� � �������� ������	
	std::map<int, std::tuple<std::string, std::string, std::string>> get_users_list_by_name(std::string UserName); 
	
	//����� �������� � �������� ��������
	std::map<int, std::tuple<std::string, std::string, std::string>> get_users_list_by_lastname(std::string UserLastName);
	
	//����� �������� � �������� email	
	std::map<int, std::tuple<std::string, std::string, std::string>> get_users_list_by_email(std::string UserEmail); 
	
	//����� id ������� � �������� ���������
	int get_user_id_by_phone(std::string UserPhone);

	/*�������� ��� �������� ���������� � �������*/

	//�������� ������ �������
	bool add_new_user(std::string UserName, std::string UserLastName, std::string UserEmail); 

	//���������� �������� ������� � ��������� id
	bool add_user_phone(int user_id, std::string user_phone);

	//��������� ������ ������� � �������� id
	bool update_user_data(int user_id, std::string new_name, std::string new_lastname, std::string new_email);

	/*�������� ���������� � �������*/

	//�������� ���������� ������ ��������  ������� � �������� id
	bool delete_user_phone(int user_id, std::string user_phone);

	//�������  ������� � �������� id
	bool delete_user(int user_id);
};