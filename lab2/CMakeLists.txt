cmake_minimum_required(VERSION 3.27)

project(engine
        DESCRIPTION "Simple Engine :>"
        VERSION 0.0.1
)

SET(CMAKE_CXX_STANDARD 23)

SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

SET(SOURCE_FILES
        source/main.cpp
        source/engine/Engine.cpp
        source/document/DocumentEditor.cpp
)

include_directories(source)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})