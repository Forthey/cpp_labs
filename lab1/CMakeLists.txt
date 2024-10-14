cmake_minimum_required(VERSION 3.27)

project(calculator
        VERSION 0.1.0
        DESCRIPTION "Simple calculator <3"
        LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(default_operators)
add_subdirectory(functions)
add_subdirectory(calculator)