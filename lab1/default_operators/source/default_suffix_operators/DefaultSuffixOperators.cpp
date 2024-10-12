#include "DefaultSuffixOperators.hpp"

#include <cmath>
#include <cstdint>
#include <stdexcept>


DefaultSuffixOperators::DefaultSuffixOperators() {
    opSymbolToInfo = {
            {"+", {4, DefaultSuffixOperators::addition}},
            {"-", {4, DefaultSuffixOperators::subtraction}},
            {"*", {5, DefaultSuffixOperators::multiplication}},
            {"/", {5, DefaultSuffixOperators::division}},
            {"%", {5, DefaultSuffixOperators::modulo}},
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
