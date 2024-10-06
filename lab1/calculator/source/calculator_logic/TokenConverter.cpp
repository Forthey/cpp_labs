#include "TokenConverter.hpp"

#include <format>

#include "../tokens/Parenthesis.hpp"


void TokenConverter::dropOperators(OperatorPtr const &op) {
    while (!stack->empty() && *op <= *stack->top()) {
        queue->push(stack->top());
        stack->pop();
    }
}

void TokenConverter::parseForPrefix(std::shared_ptr<Token> &token) {
    if (token->getType() == TokenType::OPERAND) {
        queue->push(token);
        state = ConvertState::WAITING_FOR_SUFFIX;
    } else if (token->getType() == TokenType::SUFFIX_OPERATOR) {
        auto opToken = std::dynamic_pointer_cast<Operator>(token);
        if (opToken->getType() == TokenType::OPENING_PARENTHESIS) {
            stack->push(opToken);
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
        (stack->empty() || stack->top()->getType() != TokenType::CLOSING_PARENTHESIS))
        throw std::runtime_error("ConvertError: Expected \"(\"");

    if (opToken->getType() == TokenType::OPENING_PARENTHESIS)
        stack->pop();

    if (opToken->getType() != TokenType::CLOSING_PARENTHESIS) {
        stack->push(opToken);
        state = ConvertState::WAITING_FOR_PREFIX;
    }
}

std::shared_ptr<std::queue<TokenPtr>> TokenConverter::convert(std::queue<TokenPtr> &tokens) {
    queue = std::make_shared<std::queue<TokenPtr>>();
    stack = std::make_unique<std::stack<OperatorPtr>>();

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
    if (!stack->empty())
        throw std::runtime_error("ConvertError: Expected \")\"");

    return queue;
}

