#pragma once

#include <stack>

#include "ComputableOperator.hpp"


namespace Tok {

    class SuffixOperator : public ComputableOperator {
    protected:
        std::vector<double> getNumbers(std::stack<OperandPtr> &numStack) override {
            if (numStack.size() < 2ull)
                throw std::runtime_error("CalcMultiplyError: unexpected end of expression");

            auto rightValue = numStack.top();
            numStack.pop();
            auto leftValue = numStack.top();
            numStack.pop();

            return {leftValue->getValue(), rightValue->getValue()};
        }

    public:
        explicit SuffixOperator(std::string const &name, std::uint8_t const priorityLevel,
                                std::function<double(std::vector<double> const &)> calcFunc)
                : ComputableOperator(name, priorityLevel, calcFunc) {}

        [[nodiscard]] TokenType getType() const override { return TokenType::SUFFIX_OPERATOR; }
    };

}
