#pragma once
#include "../Token.hpp"

class Operand : public Token {
public:
    [[nodiscard]] TokenType getType() const override { return TokenType::OPERAND; }

    [[nodiscard]] virtual double getValue() const = 0;
};

using OperandPtr = std::shared_ptr<Operand>;