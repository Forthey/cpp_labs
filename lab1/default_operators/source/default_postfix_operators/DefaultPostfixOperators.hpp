#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <cstdint>


class DefaultPostfixOperators {
protected:
    class opInfo {
    public:
        std::uint8_t priorityLevel;
        std::function<double(std::vector<double> const &)> calcFunction;
    };

    static std::unordered_map<char, opInfo> opSymbolToInfo;

    static double factorial(std::vector<double> const &numbers);
public:
    static bool contains(char const opName);

    static std::function<double(std::vector<double> const &)> const &getCalcFunction(char const opName);

    static std::uint8_t getPriorityLevel(char const opName);
};