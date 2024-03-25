﻿#pragma once
#include <iostream>
#include <map>
#include <vector>

struct SqlSelectQuery
{
	std::string Table;
	std::vector<std::string> Columns;
	std::map<std::string, std::string> Where_conditions;
};

class SqlSelectQueryBuilder
{
public:	
	explicit SqlSelectQueryBuilder() {};
	
	std::string BuildQuery();
	SqlSelectQueryBuilder& AddFrom(const std::string& _from);
	
	SqlSelectQueryBuilder& AddColumn(const std::string& _column);
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& _columns);
	
	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& _map);
	SqlSelectQueryBuilder& AddWhere(const std::string& _str1, const std::string& _str2);

protected:
	std::string get_table_str();
	std::string get_columns_str();
	std::string get_where_str();

private:
	SqlSelectQuery SQL_query;	
	
};

