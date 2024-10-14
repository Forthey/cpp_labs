#include "DefaultSuffixOperators.hpp"

#include <cmath>
#include <cstdint>
#include <stdexcept>

#include "DefaultPriorityRanges.hpp"


DefaultSuffixOperators::DefaultSuffixOperators() {
    opSymbolToInfo = {
            {"+", {MIN_SUFFIX_OPERATORS_PRIORITY + 1, DefaultSuffixOperators::addition}},
            {"-", {MIN_SUFFIX_OPERATORS_PRIORITY + 1, DefaultSuffixOperators::subtraction}},
            {"*", {MIN_SUFFIX_OPERATORS_PRIORITY + 2, DefaultSuffixOperators::multiplication}},
            {"/", {MIN_SUFFIX_OPERATORS_PRIORITY + 2, DefaultSuffixOperators::division}},
            {"%", {MIN_SUFFIX_OPERATORS_PRIORITY + 2, DefaultSuffixOperators::modulo}},
    };
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
    if (numbers[1] == 0.0)
        throw std::runtime_error("CalcError: Division by zero");
    return numbers[0] / numbers[1];
}

double DefaultSuffixOperators::modulo(std::vector<double> const& numbers) {
    return static_cast<double>(static_cast<std::uint32_t>(numbers[0]) % static_cast<std::uint32_t>(numbers[1]));
}
