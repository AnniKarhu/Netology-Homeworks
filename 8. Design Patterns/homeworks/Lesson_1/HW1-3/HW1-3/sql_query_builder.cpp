#include "sql_query_builder.h"


	std::string SqlSelectQueryBuilder::BuildQuery()
	{
		std::string query_str = "";

		std::string str_table = get_table_str();
		if (str_table == "")
		{
			return query_str;
		}

		std::string str_columns = get_columns_str();
		std::string str_where = get_where_str();

		query_str = "SELECT" + str_columns + " FROM " + str_table + str_where + ";";

		return query_str;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& _from)
	{
		SQL_query.Table = _from;
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& _column) 
	{
		SQL_query.Columns.push_back(_column);
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& _columns) 
	{
		std::copy(_columns.begin(), _columns.end(), std::back_inserter(SQL_query.Columns));
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& _map) 
	{
		std::copy(_map.begin(), _map.end(), std::inserter(SQL_query.Where_conditions, SQL_query.Where_conditions.begin()) );
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& _str1, const std::string& _str2)
	{
		SQL_query.Where_conditions[_str1] = _str2;
		return *this;
	}

	std::string SqlSelectQueryBuilder::get_table_str()
	{
		return SQL_query.Table;
	}

	std::string SqlSelectQueryBuilder::get_columns_str()
	{
		std::string str_columns = " * ";
		if (!SQL_query.Columns.empty())
		{
			str_columns = " " + SQL_query.Columns[0];
			for (int i = 1; i < SQL_query.Columns.size(); ++i)
			{
				str_columns += ", " + SQL_query.Columns[i];
			}
		}

		return str_columns;
	}

	std::string SqlSelectQueryBuilder::get_where_str()
	{
		std::string str_where = "";
		if (!SQL_query.Where_conditions.empty())
		{
			auto it = SQL_query.Where_conditions.begin();
			str_where = " WHERE " + it->first + "=" + it->second;

			advance(it, 1);
			for (auto it2 = it; it2 != SQL_query.Where_conditions.end(); ++it2)
			{
				str_where += " AND " + it2->first + "=" + it2->second;
			}

		}

		return str_where;
	}


