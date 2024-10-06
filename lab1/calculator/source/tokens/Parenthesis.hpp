#pragma once
#include "Token.hpp"


class OpeningParenthesis : public Operator {
public:
    OpeningParenthesis() : Operator('(') {}

    [[nodiscard]] TokenType getType() const final { return TokenType::OPENING_PARENTHESIS; }
};


class ClosingParenthesis : public Operator {
public:
    ClosingParenthesis() : Operator(')') {}

    [[nodiscard]] TokenType getType() const final { return TokenType::CLOSING_PARENTHESIS; }
};