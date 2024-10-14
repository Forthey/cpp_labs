#include "DefaultPostfixOperators.hpp"

#include <cmath>
#include <stdexcept>

#include "DefaultPriorityRanges.hpp"


DefaultPostfixOperators::DefaultPostfixOperators() {
    opSymbolToInfo = {
        {"!", {DEFAULT_POSTFIX_OPERATOR_PRIORITY, factorial}}
    };
}

double DefaultPostfixOperators::factorial(const std::vector<double> &numbers) {
    if (numbers[0] < 0.0 || std::abs(static_cast<int>(numbers[0]) - numbers[0]) > 0.0)
        throw std::runtime_error("CalcError: Invalid factorial argument");
    double result = 1.0;

    for (uint32_t i = 2; i <= numbers[0]; i++)
        result *= i;

    return result;
}
