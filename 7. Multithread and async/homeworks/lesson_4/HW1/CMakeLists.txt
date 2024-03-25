cmake_minimum_required(VERSION 3.20)
project(ProjectShapes)
add_executable(MyProject main.cpp shape.h shape.cpp transform.h transform.cpp) 

add_subdirectory(./Catch2 Catch2-build)
add_executable(MyProjectTest test-main.cpp shape.h shape.cpp transform.h transform.cpp)
target_link_libraries(MyProjectTest PRIVATE Catch2::Catch2) 