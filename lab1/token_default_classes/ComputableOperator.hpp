#pragma once

#include <stack>
#include <functional>
#include <utility>

#include "Operator.hpp"
#include "Operands.hpp"


namespace Tok {

    class ComputableOperator : public Operator {
    private:
        std::function<double(std::vector<double> const &)> calcFunc;
    protected:
        virtual std::vector<double> getNumbers(std::stack<OperandPtr> &numStack) = 0;

    public:
        explicit ComputableOperator(std::string const &name, std::uint8_t const priorityLevel,
                                    std::function<double(std::vector<double> const &)> &calcFunc)
                : Operator(name, priorityLevel), calcFunc(calcFunc) {}

        void doCalc(std::stack<OperandPtr> &numStack) {
            numStack.push(std::make_shared<Number>(calcFunc(getNumbers(numStack))));
        }
    };


    using ComputableOperatorPtr = std::shared_ptr<ComputableOperator>;

}