#include "DefaultPrefixOperators.hpp"

#include <cmath>


std::unordered_map<char, DefaultPrefixOperators::opInfo> DefaultPrefixOperators::opSymbolToInfo = {
        {'-', {7, unaryMinus}},
};

bool DefaultPrefixOperators::contains(char const opName) {
    return opSymbolToInfo.contains(opName);
}

std::function<double(std::vector<double> const &)> const &DefaultPrefixOperators::getCalcFunction(char const opName) {
    return opSymbolToInfo.at(opName).calcFunction;
}

std::uint8_t DefaultPrefixOperators::getPriorityLevel(char const opName) {
    return opSymbolToInfo.at(opName).priorityLevel;
}

double DefaultPrefixOperators::unaryMinus(std::vector<double> const &numbers) {
    return -numbers[0];
}
