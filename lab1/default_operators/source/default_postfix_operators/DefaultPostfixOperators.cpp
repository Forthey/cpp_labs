#include "DefaultPostfixOperators.hpp"

#include <cmath>
#include <stdexcept>


std::unordered_map<char, DefaultPostfixOperators::opInfo> DefaultPostfixOperators::opSymbolToInfo = {
        {'!', {100, factorial}},
};

bool DefaultPostfixOperators::contains(char const opName) {
    return opSymbolToInfo.contains(opName);
}

std::function<double(std::vector<double> const &)> const &DefaultPostfixOperators::getCalcFunction(char const opName) {
    return opSymbolToInfo.at(opName).calcFunction;
}

std::uint8_t DefaultPostfixOperators::getPriorityLevel(char const opName) {
    return opSymbolToInfo.at(opName).priorityLevel;
}

double DefaultPostfixOperators::factorial(const std::vector<double> &numbers) {
    if (numbers[0] < 0.0 || std::abs(static_cast<int>(numbers[0]) - numbers[0]) > 0.0)
        throw std::runtime_error("CalcError: Invalid factorial argument");
    double result = 1.0;

    for (uint32_t i = 2; i <= numbers[0]; i++)
        result *= i;
        
    return result;
}
