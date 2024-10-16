#pragma once

#include <vector>
#include <string>

#include "Token.hpp"

#if defined(linux) || defined(__linux__)
    #define FUNC_API __attribute__((visibility("default")))
#elif defined(_WIN64) || defined(__WIN32__)
    #if defined(COMPILE_EXPORT)
        #define FUNC_API extern "C" __declspec(dllexport)
    #else
        #define FUNC_API extern "C" __declspec(dllimport)
    #endif
#endif


FUNC_API std::string const& getName();

FUNC_API double calc(std::vector<double> const &x);

FUNC_API Tok::TokenType getType();

FUNC_API uint8_t getPriorityLevel();
