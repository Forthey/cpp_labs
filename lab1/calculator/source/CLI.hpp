#pragma once
#include <iostream>


class CLI {
public:
    static void startInteraction() {
        std::cout << "print \"exit\" to leave" << std::endl;

        std::string exprStr;
        while (true) {
            std::cout << "> ";
            std::getline(std::cin, exprStr);

            if (exprStr == "exit")
                return;

            try {
                std::cout << std::format("{} = {}\n", exprStr, Calculator::calculate(exprStr));
            } catch (std::exception& exception) {
                std::cout << exception.what() << std::endl;
            }
        }
    }
};
