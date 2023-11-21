cmake_minimum_required(VERSION 3.25)
project(task4_10)

set(CMAKE_CXX_STANDARD 14)

include_directories(source)

set(SOURCE_FILES
        source/main.cpp
        source/expert.cpp
        source/question_tree.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(task4_10 ${SOURCE_FILES})