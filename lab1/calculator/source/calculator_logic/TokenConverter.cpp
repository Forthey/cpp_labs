#include "TokenConverter.hpp"

#include <format>
#include <iostream>

#include "../tokens/Parenthesis.hpp"


void TokenConverter::dropOperators(OperatorPtr const &op) {
    while (!operatorsStack->empty() && *op <= *operatorsStack->top()) {
        resultTokens->push(operatorsStack->top());
        operatorsStack->pop();
    }
}

void TokenConverter::parseForPrefix(std::shared_ptr<Token> &token) {
    if (token->getType() == TokenType::OPERAND) {
        resultTokens->push(token);
        state = ConvertState::WAITING_FOR_SUFFIX;
    } else {
        auto opToken = std::dynamic_pointer_cast<Operator>(token);
        if (opToken->getType() == TokenType::OPENING_PARENTHESIS) {
            operatorsStack->push(opToken);
        } else {
            throw std::runtime_error(std::format(
                    "ConvertError: Expected number or \"(\", found {}", opToken->getSymbol()
            ));
        }
    }

}

void TokenConverter::parseForSuffix(std::shared_ptr<Token> &token) {
    if (token->getType() == TokenType::OPERAND)
        throw std::runtime_error("ConvertError: Expected binary operator or \")\", found number");

    auto opToken = std::dynamic_pointer_cast<Operator>(token);
    dropOperators(opToken);

    if (opToken->getType() == TokenType::OPENING_PARENTHESIS &&
        (operatorsStack->empty() || operatorsStack->top()->getType() != TokenType::CLOSING_PARENTHESIS))
        throw std::runtime_error("ConvertError: Expected \"(\"");

    if (opToken->getType() == TokenType::CLOSING_PARENTHESIS)
        operatorsStack->pop();

    if (opToken->getType() != TokenType::CLOSING_PARENTHESIS) {
        operatorsStack->push(opToken);
        state = ConvertState::WAITING_FOR_PREFIX;
    }
}

std::shared_ptr<std::queue<TokenPtr>> TokenConverter::convert(std::queue<TokenPtr> &tokens) {
    resultTokens = std::make_shared<std::queue<TokenPtr>>();
    operatorsStack = std::make_unique<std::stack<OperatorPtr>>();

    std::shared_ptr<Token> token;
    state = ConvertState::WAITING_FOR_PREFIX;

    while (true) {
        if (tokens.empty() && state == ConvertState::WAITING_FOR_PREFIX)
            throw std::runtime_error("ConvertError: Unexpected end of the expression");
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

    dropOperators(std::make_shared<ClosingParenthesis>());
    if (!operatorsStack->empty())
        throw std::runtime_error("ConvertError: Expected \")\"");

    return resultTokens;
}

