#include <iostream>
#include <format>

#include "TokenScanner.hpp"
#include "TokenConverter.hpp"

int main() {
    TokenScanner scanner;
    TokenConverter converter;

    std::string exprStr;
    std::getline(std::cin, exprStr);

    auto result = converter.convert(*scanner.buildTokens(exprStr));

    while (!result->empty()) {
        auto token = result->front();
        if (token->getType() == TokenType::NUMBER)
            std::cout << std::format("{} ", std::dynamic_pointer_cast<NumberToken>(token)->getNumber());
        else if (token->getType() == TokenType::OPERATOR)
            std::cout << std::format("{} ", std::dynamic_pointer_cast<OperatorToken>(token)->getOp());

        result->pop();
    }
	return 0;
}