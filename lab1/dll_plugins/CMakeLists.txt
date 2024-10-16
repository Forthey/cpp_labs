cmake_minimum_required(VERSION 3.27)

project(functions
        DESCRIPTION "Functions for calculator, stored in dynamic library"
        VERSION 0.1.0
        LANGUAGES CXX
)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../out/plugins)

list(APPEND plugins
        sqrt log sin cos pow
)

set(TOKEN_I_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../token_default_classes)

foreach (plugin ${plugins})
    add_library(${plugin} SHARED source/${plugin}.cpp)
    set_target_properties(${plugin} PROPERTIES PREFIX "")
    target_compile_definitions(${plugin} PRIVATE COMPILE_EXPORT)
    target_include_directories(${plugin} PRIVATE ${TOKEN_I_SOURCE})

    add_custom_command(
            TARGET ${plugin} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/source/export.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/include/export.hpp
    )
endforeach ()
