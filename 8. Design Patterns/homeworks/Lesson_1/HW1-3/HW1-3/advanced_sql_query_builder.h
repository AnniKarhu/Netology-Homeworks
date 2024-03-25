#pragma once
#include "sql_query_builder.h"


struct Advanced_Where_conditions
{
	std::string str_1;
	std::string str_2;
	std::string condition;
};

struct AdvSqlSelectQuery : public SqlSelectQuery
{
  std::vector<Advanced_Where_conditions> Adv_Where_conditions;
};


class AdvancedSqlSelectQueryBuilder : public  SqlSelectQueryBuilder
{
public:
	explicit AdvancedSqlSelectQueryBuilder() {};
	SqlSelectQueryBuilder& AddWhereAdv(const std::string& _str1, const std::string& _str2, const std::string&  _cond);

protected:
	std::string get_where_str() override;

private:
	AdvSqlSelectQuery SQL_query;

};