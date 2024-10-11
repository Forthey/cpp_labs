#pragma once

#include <memory>

namespace Tok {

    enum TokenType {
        SUFFIX_OPERATOR = 0,
        PREFIX_OPERATOR,
        OPERAND,
        OPENING_PARENTHESIS,
        CLOSING_PARENTHESIS
    };

    class Token {
    public:
        [[nodiscard]] virtual TokenType getType() const = 0;

        virtual ~Token() = default;
    };

    using TokenPtr = std::shared_ptr<Token>;

}