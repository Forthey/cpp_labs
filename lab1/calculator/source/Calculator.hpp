#pragma once

#include <string>


class Calculator {
public:
    [[nodiscard]] static double calculate(std::string const& exprStr);
};
