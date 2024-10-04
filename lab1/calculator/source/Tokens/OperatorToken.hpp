#pragma once
#include "DefaultToken.hpp"

class OperatorToken : public Token {
    char const op;
public:
    explicit OperatorToken(char const op) : Token(TokenType::OPERATOR), op(op) {}

    [[nodiscard]] char getOp() const { return op; }
};
