#pragma once
#pragma once

#include <stack>

#include "ComputableOperator.hpp"


class PrefixOperator : public ComputableOperator {
protected:
    std::vector<double> getNumbers(std::stack<OperandPtr> &numStack) override {
        if (numStack.size() < 1ull)
            throw std::runtime_error("CalcMultiplyError: unexpected end of expression");

        auto value = numStack.top();
        numStack.pop();

        return {value->getValue()};
    }

public:
    explicit PrefixOperator(std::string const &name, std::uint8_t const priorityLevel,
    std::function<double(std::vector<double> const &)> calcFunc)
    : ComputableOperator(name, priorityLevel, calcFunc) {}

    [[nodiscard]] TokenType getType() const override { return TokenType::PREFIX_OPERATOR; }
};
