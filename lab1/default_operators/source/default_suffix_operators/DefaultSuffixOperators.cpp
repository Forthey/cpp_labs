#include "DefaultSuffixOperators.hpp"

#include <cmath>
#include <cstdint>


std::unordered_map<char, DefaultSuffixOperators::opInfo> DefaultSuffixOperators::opSymbolToInfo = {
        {'+', {4, DefaultSuffixOperators::addition}},
        {'-', {4, DefaultSuffixOperators::subtraction}},
        {'*', {5, DefaultSuffixOperators::multiplication}},
        {'/', {5, DefaultSuffixOperators::division}},
        {'%', {5, DefaultSuffixOperators::modulo}},
        {'^', {6, DefaultSuffixOperators::power}},
};

bool DefaultSuffixOperators::contains(char const opName) {
    return opSymbolToInfo.contains(opName);
}

std::function<double(std::vector<double> const&)> const& DefaultSuffixOperators::getCalcFunction(char const opName) {
    return opSymbolToInfo.at(opName).calcFunction;
}

std::uint8_t DefaultSuffixOperators::getPriorityLevel(char const opName) {
    return opSymbolToInfo.at(opName).priorityLevel;
}

double DefaultSuffixOperators::addition(std::vector<double> const& numbers) {
    return numbers[0] + numbers[1];
}

double DefaultSuffixOperators::subtraction(std::vector<double> const& numbers) {
    return numbers[0] - numbers[1];
}

double DefaultSuffixOperators::multiplication(std::vector<double> const& numbers) {
    return numbers[0] * numbers[1];
}

double DefaultSuffixOperators::division(std::vector<double> const& numbers) {
    return numbers[0] / numbers[1];
}

double DefaultSuffixOperators::modulo(std::vector<double> const& numbers) {
    return static_cast<double>(static_cast<std::uint32_t>(numbers[0]) % static_cast<std::uint32_t>(numbers[1]));
}

double DefaultSuffixOperators::power(std::vector<double> const& numbers) {
    return std::pow(numbers[0], numbers[1]);
}
