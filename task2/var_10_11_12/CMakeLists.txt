cmake_minimum_required(VERSION 3.25)
project(task2_12)

set(CMAKE_CXX_STANDARD 14)

include_directories(source)

add_executable(task2_12
        source/graph.cpp
        source/graph.hpp
        source/list.hpp
        source/main.cpp)
