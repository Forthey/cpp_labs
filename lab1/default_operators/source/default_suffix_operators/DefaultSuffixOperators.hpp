#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <cstdint>


class DefaultSuffixOperators {
    class opInfo {
    public:
        std::uint8_t priorityLevel;
        std::function<double(std::vector<double> const &)> calcFunction;
    };

    static std::unordered_map<char, opInfo> opSymbolToInfo;
public:
    static bool contains(char const opName);

    static std::function<double(std::vector<double> const &)> const &getCalcFunction(char const opName);

    static std::uint8_t getPriorityLevel(char const opName);

    static double addition(std::vector<double> const &numbers);

    static double subtraction(std::vector<double> const &numbers);

    static double multiplication(std::vector<double> const &numbers);

    static double division(std::vector<double> const &numbers);

    static double modulo(std::vector<double> const &numbers);
};