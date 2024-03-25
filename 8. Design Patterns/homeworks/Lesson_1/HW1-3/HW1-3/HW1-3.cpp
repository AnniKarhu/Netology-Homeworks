#include <iostream>
#include <assert.h>

//#include "sql_query_builder.h"
#include "advanced_sql_query_builder.h"

int main()
{
    
    AdvancedSqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone" });
    query_builder.AddFrom("students");
    query_builder.AddWhereAdv("id", "42", ">");
    
   
        
    std::cout << query_builder.BuildQuery() << "\n";
    assert(query_builder.BuildQuery() == "SELECT name, phone FROM students WHERE id>42;");

    std::map<std::string, std::string> where_map;
    where_map["name"] = "John";
    query_builder.AddWhere(where_map);
    std::cout << query_builder.BuildQuery() << "\n";

    return 0;
}
