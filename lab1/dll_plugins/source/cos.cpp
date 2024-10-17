#include "export.hpp"

#include <cmath>
#include <stdexcept>

#include "DefaultPriorityRanges.hpp"

std::string const name = "cos";

std::string const& getName() {
    return name;
}

double calc(std::vector<double> const &x) {
    return static_cast<double>(std::cos(static_cast<long double>(x[0])));
}

Tok::TokenType getType() {
    return Tok::TokenType::PREFIX_OPERATOR;
}

uint8_t getPriorityLevel() {
    return DEFAULT_FUNCTION_PRIORITY;
}