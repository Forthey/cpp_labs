#include <iostream>
#include <format>

#include "Calculacor/Calculator.hpp"

int main() {
    std::string exprStr = "3 + 5 * 6 - (7 + 8)";
    std::cout << "> ";
    std::getline(std::cin, exprStr);

    try {
        std::cout << std::format("{} = {}\n", exprStr, Calculator::calculate(exprStr));
    } catch (std::exception& exception) {
        std::cout << exception.what() << std::endl;
        return 1;
    }
	return 0;
}