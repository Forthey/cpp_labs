#include "PolishCalculator.hpp"

#include <stack>
#include <iostream>
#include <format>

#include "../tokens/operands/Operand.hpp"
#include "../tokens/ComputableOperator.hpp"


double PolishCalculator::calculate(std::queue<TokenPtr>& tokens) {
    std::stack<OperandPtr> operandStack;

    while (!tokens.empty()) {
        auto token = tokens.front();
        tokens.pop();

//        if (token->getType() == TokenType::OPERAND)
//            std::cout << std::format("{} ", std::dynamic_pointer_cast<Operand>(token)->getValue());
//        else if (token->getType() == TokenType::SUFFIX_OPERATOR)
//            std::cout << std::format("{} ", std::dynamic_pointer_cast<Operator>(token)->getSymbol());

        switch (token->getType()) {
            case SUFFIX_OPERATOR:
            case PREFIX_OPERATOR:
                std::dynamic_pointer_cast<ComputableOperator>(token)->doCalc(operandStack);
                break;
            case OPERAND:
                operandStack.push(std::dynamic_pointer_cast<Operand>(token));
                break;
            case OPENING_PARENTHESIS:
            case CLOSING_PARENTHESIS:
                break;
        }
    }

    return operandStack.top()->getValue();
}
