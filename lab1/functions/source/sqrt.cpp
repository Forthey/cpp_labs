#include "export.hpp"

#include <cmath>
#include <stdexcept>


std::string const name = "sqrt";

std::string const& getName() {
    return name;
}

double calc(std::vector<double> const &x) {
    if (x[0] < 0.0) {
        throw std::runtime_error("CalcError: sqrt argument must be more than 0");
    }
    return static_cast<double>(std::sqrt(static_cast<long double>(x[0])));
}

Tok::TokenType getType() {
    return Tok::TokenType::PREFIX_OPERATOR;
}

uint8_t getPriorityLevel() {
    return DEFAULT_FUNCTION_PRIORITY;
}