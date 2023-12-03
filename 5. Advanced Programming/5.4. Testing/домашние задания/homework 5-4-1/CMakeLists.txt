cmake_minimum_required(VERSION 3.20)
project(DoubleLinkedList)
add_executable(DoubleLinkedList homework-5-4.cpp DoubleLinkedList.h DoubleLinkedList.cpp) 

add_subdirectory(./Catch2 Catch2-build)
add_executable(DoubleLinkedListTest test_homework-5-4.cpp DoubleLinkedList.h DoubleLinkedList.cpp)
target_link_libraries(DoubleLinkedListTest PRIVATE Catch2::Catch2) 