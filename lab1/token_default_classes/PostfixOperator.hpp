#pragma once

#include <stack>

#include "PrefixOperator.hpp"


namespace Tok {

    class PostfixOperator : public PrefixOperator {
    public:
        explicit PostfixOperator(std::string const &name, std::uint8_t const priorityLevel,
                                std::function<double(std::vector<double> const &)> calcFunc)
                : PrefixOperator(name, priorityLevel, calcFunc) {}

        [[nodiscard]] TokenType getType() const override { return TokenType::POSTFIX_OPERATOR; }
    };

}