#include "TokenConverter.hpp"

#include <format>
#include <iostream>

#include "Parenthesis.hpp"
#include "CalcException.hpp"


void TokenConverter::dropOperators(Tok::OperatorPtr const &op) {
    while (!operatorsStack->empty() && *op <= *operatorsStack->top()) {
        resultTokens->push(operatorsStack->top());
        operatorsStack->pop();
    }
}

void TokenConverter::parseForPrefix(std::shared_ptr<Tok::Token> &token) {
    if (token->getType() == Tok::TokenType::OPERAND) {
        resultTokens->push(token);
        state = ConvertState::WAITING_FOR_SUFFIX;
        return;
    }

    auto opToken = std::dynamic_pointer_cast<Tok::Operator>(token);
    if (opToken->getType() == Tok::TokenType::OPENING_PARENTHESIS ||
        opToken->getType() == Tok::TokenType::PREFIX_OPERATOR) {
        operatorsStack->push(opToken);
    } else {
        throw CalcException("ConvertError", std::format("Expected number or \"(\", found {}", opToken->getName()));
    }
}

void TokenConverter::parseForSuffix(std::shared_ptr<Tok::Token> &token) {
    if (token->getType() == Tok::TokenType::OPERAND)
        throw CalcException("ConvertError", "Expected binary operator or \")\", found number");

    auto opToken = std::dynamic_pointer_cast<Tok::Operator>(token);
    dropOperators(opToken);

    if (opToken->getType() == Tok::TokenType::OPENING_PARENTHESIS &&
        (operatorsStack->empty() || operatorsStack->top()->getType() != Tok::TokenType::CLOSING_PARENTHESIS))
        throw CalcException("ConvertError", "Expected \"(\"");

    if (opToken->getType() == Tok::TokenType::CLOSING_PARENTHESIS)
        operatorsStack->pop();
    else if (opToken->getType() != Tok::TokenType::CLOSING_PARENTHESIS) {
        operatorsStack->push(opToken);
        if (opToken->getType() != Tok::TokenType::POSTFIX_OPERATOR)
            state = ConvertState::WAITING_FOR_PREFIX;
    }
}

std::shared_ptr<std::queue<Tok::TokenPtr>> TokenConverter::convert(std::queue<Tok::TokenPtr> &tokens) {
    resultTokens = std::make_shared<std::queue<Tok::TokenPtr>>();
    operatorsStack = std::make_unique<std::stack<Tok::OperatorPtr>>();

    std::shared_ptr<Tok::Token> token;
    state = ConvertState::WAITING_FOR_PREFIX;

    while (true) {
        if (tokens.empty() && state == ConvertState::WAITING_FOR_PREFIX)
            throw CalcException("ConvertError", "Unexpected end of the expression");
        if (tokens.empty() && state == ConvertState::WAITING_FOR_SUFFIX) {
            break;
        } else {
            token = tokens.front();
            tokens.pop();
        }

        switch (state) {
            case WAITING_FOR_PREFIX:
                parseForPrefix(token);
                break;
            case WAITING_FOR_SUFFIX:
                parseForSuffix(token);
                break;
        }
    }

    dropOperators(std::make_shared<Tok::ClosingParenthesis>());
    if (!operatorsStack->empty())
        throw CalcException("ConvertError", "Expected \")\"");
    operatorsStack.reset();

    return resultTokens;
}

