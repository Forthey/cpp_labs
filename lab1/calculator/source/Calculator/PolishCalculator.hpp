#pragma once

#include <memory>
#include <queue>
#include <stack>

#include "Token.hpp"
#include "Operand.hpp"


class PolishCalculator {
    std::shared_ptr<std::stack<Tok::OperandPtr>> operandStack;

    void parseToken(Tok::TokenPtr &token);
public:
    double calculate(std::queue<Tok::TokenPtr> &tokens);
};
