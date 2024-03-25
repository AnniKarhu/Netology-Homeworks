#include "advanced_sql_query_builder.h"

SqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddWhereAdv(const std::string& _str1, const std::string& _str2, const std::string& _cond)
{
	if (!((_cond == "<") || (_cond == ">") || (_cond == "=")))
	{
		return *this;
	}
	
	Advanced_Where_conditions _new_cond;
	_new_cond.str_1 = _str1;
	_new_cond.str_2 = _str2;
	_new_cond.condition = _cond;

	SQL_query.Adv_Where_conditions.push_back(_new_cond);
}

std::string AdvancedSqlSelectQueryBuilder::get_where_str() 
{
	std::string result_str = SqlSelectQueryBuilder::get_where_str();
	
	if (!SQL_query.Adv_Where_conditions.empty())
	{
		std::string zero_cond = SQL_query.Adv_Where_conditions[0].str_1 + SQL_query.Adv_Where_conditions[0].condition+ SQL_query.Adv_Where_conditions[0].str_2;
		if (result_str == "")
		{
			result_str = " WHERE " + zero_cond;
		}
		else
			result_str += " AND " + zero_cond;

		for (int i = 1; i < SQL_query.Adv_Where_conditions.size(); ++i)
		{
			result_str += " AND " + SQL_query.Adv_Where_conditions[i].str_1 + SQL_query.Adv_Where_conditions[i].condition + SQL_query.Adv_Where_conditions[i].str_2;
		}
	}	
	
	return result_str;
}