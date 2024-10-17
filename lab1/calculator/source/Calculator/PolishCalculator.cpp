#include "PolishCalculator.hpp"

#include "ComputableOperator.hpp"


double PolishCalculator::calculate(std::queue<Tok::TokenPtr>& tokens) {
    operandStack = std::make_shared<std::stack<Tok::OperandPtr>>();

    while (!tokens.empty()) {
        auto token = tokens.front();
        tokens.pop();
        parseToken(token);
    }

    auto result = operandStack->top()->getValue();
    operandStack.reset();

    return result;
}

void PolishCalculator::parseToken(Tok::TokenPtr &token) {
    switch (token->getType()) {
        case Tok::PREFIX_OPERATOR:
        case Tok::SUFFIX_OPERATOR:
        case Tok::POSTFIX_OPERATOR:
            std::dynamic_pointer_cast<Tok::ComputableOperator>(token)->doCalc(*operandStack);
            break;
        case Tok::OPERAND:
            operandStack->push(std::dynamic_pointer_cast<Tok::Operand>(token));
            break;
        case Tok::OPENING_PARENTHESIS:
        case Tok::CLOSING_PARENTHESIS:
            break;
    }
}
