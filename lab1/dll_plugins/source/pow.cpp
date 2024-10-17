#include "export.hpp"

#include <cmath>
#include <stdexcept>

std::string const name = "^";

std::string const& getName() {
    return name;
}

double calc(std::vector<double> const &x) {
    if (x[0] < 0.0 && std::abs(static_cast<int>(x[1]) - x[1]) > 0.0)
        throw CalcException("CalcError", "Exponentiation of a negative number");
    return std::pow(x[0], x[1]);
}

Tok::TokenType getType() {
    return Tok::TokenType::SUFFIX_OPERATOR;
}

uint8_t getPriorityLevel() {
    return MIN_SUFFIX_OPERATORS_PRIORITY + 3;
}