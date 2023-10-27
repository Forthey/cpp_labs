cmake_minimum_required(VERSION 3.25)
project(task2_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(source)

add_executable(task2_1
        source/notebook.cpp
        source/list.hpp
        source/main.cpp)
