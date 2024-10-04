#pragma once
#include "DefaultToken.hpp"

class NumberToken : public Token {
    double const number;
public:
    explicit NumberToken(double const number) : Token(TokenType::NUMBER), number(number) {}

    [[nodiscard]] double getNumber() const { return number; }
};