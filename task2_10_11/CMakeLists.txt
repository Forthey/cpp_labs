cmake_minimum_required(VERSION 3.25)
project(task2_10_11)

set(CMAKE_CXX_STANDARD 14)

include_directories(source)

set(SOURCE_FILES
        source/graph.cpp
        source/graph.hpp
        source/list.hpp
        source/main.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task2_10_11 ${SOURCE_FILES})