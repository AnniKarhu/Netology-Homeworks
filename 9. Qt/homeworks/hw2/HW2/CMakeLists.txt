cmake_minimum_required(VERSION 3.5)

project(HW2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS Network)

add_executable(HW2
  main.cpp
)
target_link_libraries(HW2 PRIVATE Qt6::Core)
target_link_libraries(HW2 PRIVATE Qt6::Sql)
target_link_libraries(HW2 PRIVATE Qt6::Network)

install(TARGETS HW2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
