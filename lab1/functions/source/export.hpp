#pragma once

#include <vector>
#include <string>

#include "Token.hpp"


extern "C" __declspec(dllexport) std::string const& getName();

extern "C" __declspec(dllexport) double calc(std::vector<double> const &x);

extern "C" __declspec(dllexport) Tok::TokenType getType();

extern "C" __declspec(dllexport) uint8_t getPriorityLevel();