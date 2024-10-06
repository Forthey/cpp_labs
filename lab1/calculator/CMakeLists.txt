cmake_minimum_required(VERSION 3.27)

project(calculator
        VERSION 0.1.0
        DESCRIPTION "Simple calculator <3"
        LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE_FILES
        source/main.cpp
        source/calculator_logic/TokenScanner.cpp
        source/calculator_logic/TokenConverter.cpp
        source/calculator_logic/PolishCalculator.cpp
        source/tokens/priority_level/PriorityLevelStorage.cpp
        source/Calculator.cpp
        source/Calculator.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
