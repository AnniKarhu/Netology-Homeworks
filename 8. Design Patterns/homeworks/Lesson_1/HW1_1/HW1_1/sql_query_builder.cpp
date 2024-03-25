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

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& _column)
	{
		SQL_query.Columns.push_back(_column);
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& _from)
	{
		SQL_query.Table = _from;
		return *this;
	}

	SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& _str1, const std::string& _str2)
	{
		std::pair<std::string, std::string> _pair;
		_pair.first = _str1;
		_pair.second = _str2;
		SQL_query.Where_conditions.push_back(_pair);
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
			str_where = " WHERE " + SQL_query.Where_conditions[0].first + "=" + (SQL_query.Where_conditions)[0].second;
			for (int i = 1; i < SQL_query.Where_conditions.size(); ++i)
			{
				str_where += " AND " + SQL_query.Where_conditions[i].first + "=" + (SQL_query.Where_conditions)[i].second;
			}
		}

		return str_where;
	}


