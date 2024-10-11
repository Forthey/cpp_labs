#pragma once
#include <vector>
#include <string>


extern "C" __declspec(dllexport) std::string const& getName();

extern "C" __declspec(dllexport) double calc(std::vector<double> const &x);
