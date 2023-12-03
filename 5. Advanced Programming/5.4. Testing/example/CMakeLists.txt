cmake_minimum_required(VERSION 3.20)
project(MyProject)
add_executable(MyProject main.cpp Factorial.h Factorial.cpp) 

add_subdirectory(./Catch2 Catch2-build)
add_executable(MyProjectTest test-main.cpp Factorial.h Factorial.cpp)
target_link_libraries(MyProjectTest PRIVATE Catch2::Catch2) 