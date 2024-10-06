#pragma once

#include <stack>
#include "../ComputableOperator.hpp"


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

    explicit SuffixOperator(char const symbol) : ComputableOperator(symbol) {}
public:
    [[nodiscard]] TokenType getType() const override { return TokenType::SUFFIX_OPERATOR; }
};

