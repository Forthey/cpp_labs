cmake_minimum_required(VERSION 3.27)

project(default_operators)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

set(SOURCE_FILES
        source/default_suffix_operators/DefaultSuffixOperators.cpp
        source/default_prefix_operators/DefaultPrefixOperators.cpp
        source/default_postfix_operators/DefaultPostfixOperators.cpp
        source/DefaultOperators.cpp
)

set(TOKEN_I_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../token_default_classes)
set(CALC_EXCEPTION_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/../calc_custom_exception)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
        include
        ${TOKEN_I_SOURCE}
        ${CALC_EXCEPTION_SOURCE}
)

set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".lib")

file(GLOB_RECURSE header_files "source/*.hpp")
foreach (header_file_path ${header_files})
    get_filename_component(filename ${header_file_path} NAME)
    message(${CMAKE_CURRENT_SOURCE_DIR}/include/${filename})
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${header_file_path}
            ${CMAKE_CURRENT_SOURCE_DIR}/include/${filename}
    )
endforeach ()