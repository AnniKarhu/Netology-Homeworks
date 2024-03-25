#include <iostream>
#include <assert.h>

#include "sql_query_builder.h"

int main()
{
    SqlSelectQueryBuilder query_builder;
    
    query_builder.AddFrom("students");

    std::vector<std::string> _columns_vector;
    _columns_vector.push_back("name");
    _columns_vector.push_back("phone");
    query_builder.AddColumns(_columns_vector);


    std::map<std::string, std::string> where_map;
    where_map["id"] = "42";
    where_map["name"] = "John";
    query_builder.AddWhere(where_map);     

    std::cout << query_builder.BuildQuery();

    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id=42 AND name=John;");


    return 0;
}