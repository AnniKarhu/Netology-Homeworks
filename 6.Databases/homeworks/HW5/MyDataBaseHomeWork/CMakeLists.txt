cmake_minimum_required(VERSION 3.20)

set(PostgreSQL_ADDITIONAL_VERSIONS "16")

project(MyDataBaseHomeWork)

add_subdirectory("D:\\Netology\\6.Databases\\secret\\libpqxx-7.8.1" libpqxx-build)

add_executable(MyDataBaseHomeWork main.cpp "data_base.h" "data_base.cpp" "user_interface.h" "user_interface.cpp")

target_compile_features(MyDataBaseHomeWork PRIVATE cxx_std_17)

target_link_libraries(MyDataBaseHomeWork PRIVATE pqxx)