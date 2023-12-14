cmake_minimum_required(VERSION 3.25)
project(task5_1)

set(CMAKE_CXX_STANDARD 14)

#include_directories(source)

set(SOURCE_FILES
        source/console.cpp
        source/tree.cpp
        source/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task5_1 ${SOURCE_FILES})