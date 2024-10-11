#include "PolishCalculator.hpp"

#include <stack>
#include <iostream>
#include <format>

#include "Operand.hpp"
#include "ComputableOperator.hpp"


double PolishCalculator::calculate(std::queue<Tok::TokenPtr>& tokens) {
    std::stack<Tok::OperandPtr> operandStack;

    while (!tokens.empty()) {
        auto token = tokens.front();
        tokens.pop();

//        if (token->getType() == Tok::TokenType::OPERAND)
//            std::cout << std::format("{} ", std::dynamic_pointer_cast<Tok::Operand>(token)->getValue());
//        else if (token->getType() == Tok::TokenType::SUFFIX_OPERATOR || token->getType() == Tok::TokenType::PREFIX_OPERATOR)
//            std::cout << std::format("{} ", std::dynamic_pointer_cast<Tok::Operator>(token)->getName());

        switch (token->getType()) {
            case Tok::SUFFIX_OPERATOR:
            case Tok::PREFIX_OPERATOR:
                std::dynamic_pointer_cast<Tok::ComputableOperator>(token)->doCalc(operandStack);
                break;
            case Tok::OPERAND:
                operandStack.push(std::dynamic_pointer_cast<Tok::Operand>(token));
                break;
            case Tok::OPENING_PARENTHESIS:
            case Tok::CLOSING_PARENTHESIS:
                break;
        }
    }

    return operandStack.top()->getValue();
}
