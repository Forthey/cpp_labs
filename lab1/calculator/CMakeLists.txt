cmake_minimum_required(VERSION 3.27)

project(calculator
        VERSION 0.1.0
        DESCRIPTION "Simple calculator <3"
        LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../out)

SET(SOURCE_FILES
        source/main.cpp
        source/Calculacor/TokenScanner.cpp
        source/Calculacor/TokenConverter.cpp
        source/Calculacor/PolishCalculator.cpp
        source/Calculacor/Calculator.cpp
        source/Calculacor/Calculator.hpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


set(TOKEN_I_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../token_default_classes)
set(DEFAULT_OP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../default_operators)

target_include_directories(${PROJECT_NAME} PRIVATE ${TOKEN_I_SOURCE} ${DEFAULT_OP_SOURCE}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${DEFAULT_OP_SOURCE}/lib/default_operators.lib)