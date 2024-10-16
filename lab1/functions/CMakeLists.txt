cmake_minimum_required(VERSION 3.27)

project(functions
        DESCRIPTION "Functions for calculator, stored in dynamic library"
        VERSION 0.1.0
        LANGUAGES CXX
)

set(LIBRARY_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/../out/plugins)

list(APPEND functions
        sqrt log sin cos pow
)

set(TOKEN_I_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../token_default_classes)

foreach(func ${functions})
    add_library(${func} SHARED source/${func}.cpp)
    set_target_properties(${func} PROPERTIES PREFIX "")
    target_compile_definitions(${func} PRIVATE COMPILE_EXPORT)
    target_include_directories(${func} PRIVATE ${TOKEN_I_SOURCE})


    add_custom_command(
            TARGET ${func} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/source/export.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/export.hpp
    )
endforeach()
