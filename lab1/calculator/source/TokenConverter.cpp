#include <format>
#include "TokenConverter.hpp"

std::unordered_map<char, uint8_t> const TokenConverter::opPriority = {
        {'+', 4},
        {'-', 4},
        {'*', 5},
        {'/', 5},
        {'%', 5},
        {'^', 6},
        {'(', 0},
        {')', 1},
};

void TokenConverter::dropOperators(char const op) {

    while (!stack->empty() && opPriority.at(op) <= opPriority.at(stack->top()->getOp())) {
        queue->push(stack->top());
        stack->pop();
    }
}

void TokenConverter::parseForPrefix(std::shared_ptr<Token> &token) {
    if (token->getType() == TokenType::NUMBER) {
        queue->push(token);
        state = ConvertState::WAITING_FOR_SUFFIX;
    } else if (token->getType() == TokenType::OPERATOR) {
        auto opToken = std::dynamic_pointer_cast<OperatorToken>(token);
        if (opToken->getOp() == '(') {
            stack->push(opToken);
        } else {
            throw std::runtime_error(std::format(
                    "ConvertError: Expected number or \"(\", found {}", opToken->getOp()
            ));
        }
    }

}

void TokenConverter::parseForSuffix(std::shared_ptr<Token> &token) {
    if (token->getType() == TokenType::NUMBER)
        throw std::runtime_error("ConvertError: Expected binary operator or \")\", found number");

    auto opToken = std::dynamic_pointer_cast<OperatorToken>(token);
    dropOperators(opToken->getOp());

    if (opToken->getOp() == ')' && (stack->empty() || stack->top()->getOp() != '('))
        throw std::runtime_error("ConvertError: Expected \"(\"");

    if (opToken->getOp() == ')')
        stack->pop();

    if (opToken->getOp() != ')') {
        stack->push(opToken);
        state = ConvertState::WAITING_FOR_PREFIX;
    }
}

std::shared_ptr<std::queue<std::shared_ptr<Token>>>
TokenConverter::convert(std::queue<std::shared_ptr<Token>> &tokens) {
    queue = std::make_shared<std::queue<std::shared_ptr<Token>>>();
    stack = std::make_unique<std::stack<std::shared_ptr<OperatorToken>>>();

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

    dropOperators(')');
    if (!stack->empty())
        throw std::runtime_error("ConvertError: Expected \")\"");

    return queue;
}

