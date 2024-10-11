#pragma once
#include "PrefixOperator.hpp"


class Function : PrefixOperator {
protected:
    std::vector<double> getNumbers(std::stack<OperandPtr> &numStack) override {
        if (numStack.size() < 1ull)
            throw std::runtime_error("CalcMultiplyError: unexpected end of expression");

        auto value = numStack.top();
        numStack.pop();

        return {value->getValue()};
    }

public:
    explicit Function(std::string const &name, std::function<double(std::vector<double> const &)> calcFunc)
    : PrefixOperator(name, 3, calcFunc) {}

    [[nodiscard]] TokenType getType() const override { return TokenType::PREFIX_OPERATOR; }
};
