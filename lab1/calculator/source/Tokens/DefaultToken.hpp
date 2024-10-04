#pragma once

enum TokenType {
    OPERATOR = 0,
    NUMBER,
    FUNCTION,
    VARIABLE
};

class Token {
    TokenType type;
public:
    explicit Token(TokenType type) : type(type) {}

    [[nodiscard]] TokenType getType() const { return type; }

    virtual ~Token() = default;
};
