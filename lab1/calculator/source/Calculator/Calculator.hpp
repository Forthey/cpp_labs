#pragma once
#include <string>

#include "TokenScanner.hpp"
#include "TokenConverter.hpp"
#include "PolishCalculator.hpp"


class Calculator {
    TokenConverter converter;
    TokenScanner scanner;
    PolishCalculator polishCalculator;
public:
    [[nodiscard]] double calculate(std::string const& exprStr);
};
