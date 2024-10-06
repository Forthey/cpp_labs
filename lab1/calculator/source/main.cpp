#include <iostream>
#include <format>

#include "calculator_logic/TokenScanner.hpp"
#include "calculator_logic/TokenConverter.hpp"

int main() {
    TokenScanner scanner;
    TokenConverter converter;

    std::string exprStr;
    std::getline(std::cin, exprStr);

    auto result = converter.convert(*scanner.buildTokens(exprStr));

    while (!result->empty()) {
        auto token = result->front();
        if (token->getType() == TokenType::OPERAND)
            std::cout << std::format("{} ", std::dynamic_pointer_cast<Operand>(token)->getValue());
        else if (token->getType() == TokenType::SUFFIX_OPERATOR)
            std::cout << std::format("{} ", std::dynamic_pointer_cast<Operator>(token)->getSymbol());

        result->pop();
    }
	return 0;
}