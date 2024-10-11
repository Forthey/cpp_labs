#pragma once
#include "Operator.hpp"


class OpeningParenthesis : public Operator {
public:
    OpeningParenthesis() : Operator("(", 0) {}

    [[nodiscard]] TokenType getType() const final { return TokenType::OPENING_PARENTHESIS; }
};


class ClosingParenthesis : public Operator {
public:
    ClosingParenthesis() : Operator(")", 1) {}

    [[nodiscard]] TokenType getType() const final { return TokenType::CLOSING_PARENTHESIS; }
};