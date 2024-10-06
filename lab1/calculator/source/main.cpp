#include <iostream>
#include <format>

#include "Calculator.hpp"

int main() {
    std::string exprStr = "3 + 5 * 6 - (7 + 8)";
    std::cout << "> ";
    std::getline(std::cin, exprStr);

    std::cout << std::format("{} = {}\n", exprStr, Calculator::calculate(exprStr));
	return 0;
}