#pragma once
#include <iostream>


class CLI {
public:
    static void startInteraction() {
        std::cout << R"(print "exit" or ":q" to leave)" << std::endl;

        std::string exprStr;
        Calculator calculator;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, exprStr);

            if (exprStr == "exit" || exprStr == ":q")
                return;

            try {
                std::cout << std::format("{} = {}\n", exprStr, calculator.calculate(exprStr));
            } catch (std::exception& exception) {
                std::cout << exception.what() << std::endl;
            }
        }
    }
};
