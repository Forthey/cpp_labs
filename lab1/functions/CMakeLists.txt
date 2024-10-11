cmake_minimum_required(VERSION 3.27)

project(functions
        DESCRIPTION "Functions for calculator, stored in dynamic library"
        VERSION 0.1.0
        LANGUAGES CXX
)

set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/../out)

set(SOURCE_FILES
        source/Sqrt.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ../token_default_classes)