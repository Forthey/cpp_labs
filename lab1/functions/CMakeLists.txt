cmake_minimum_required(VERSION 3.27)

project(functions
        DESCRIPTION "Functions for calculator, stored in dynamic library"
        VERSION 0.1.0
        LANGUAGES CXX
)

set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/../out/funcs)

list(APPEND functions
        sqrt log sin cos
)

foreach(func ${functions})
    add_library(${func} SHARED source/${func}.cpp)
    set_target_properties(${func} PROPERTIES PREFIX "")
endforeach()