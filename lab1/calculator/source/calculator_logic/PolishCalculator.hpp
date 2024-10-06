#pragma once
#include <memory>
#include <queue>

#include "../tokens/Token.hpp"

class PolishCalculator {
public:
    static void calculate(std::queue<TokenPtr> const& tokens);
};
