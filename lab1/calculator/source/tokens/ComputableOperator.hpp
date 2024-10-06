#pragma once
#include <stack>

#include "Operator.hpp"
#include "operands/Operands.hpp"
#include "priority_level/PriorityLevelStorage.hpp"

class ComputableOperator : public Operator {
protected:
    virtual std::vector<double> getNumbers(std::stack<OperandPtr>& numStack) = 0;
    // TODO add templates
    virtual double calculate(std::vector<double> const& numbers) = 0;

    explicit ComputableOperator(char const symbol) : Operator(symbol) {}
public:
    void doCalc(std::stack<OperandPtr>& numStack) {
        numStack.push(std::make_shared<Number>(calculate(getNumbers(numStack))));
    }
};


using ComputableOperatorPtr = std::shared_ptr<ComputableOperator>;