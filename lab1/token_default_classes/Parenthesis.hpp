#pragma once
#include "Operator.hpp"


namespace Tok {

    class OpeningParenthesis : public Operator {
    public:
        OpeningParenthesis() : Operator("(", OPENING_PARENTHESIS_PRIORITY) {}

        [[nodiscard]] TokenType getType() const final { return TokenType::OPENING_PARENTHESIS; }
    };


    class ClosingParenthesis : public Operator {
    public:
        ClosingParenthesis() : Operator(")", CLOSING_PARENTHESIS_PRIORITY) {}

        [[nodiscard]] TokenType getType() const final { return TokenType::CLOSING_PARENTHESIS; }
    };

}