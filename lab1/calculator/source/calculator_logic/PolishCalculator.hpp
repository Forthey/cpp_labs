#pragma once
#include <memory>
#include <queue>

#include "../tokens/Token.hpp"

class PolishCalculator {
public:
    static double calculate(std::queue<TokenPtr>& tokens);
};
