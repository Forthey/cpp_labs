#pragma once
#include <iostream>

#include "CalcException.hpp"


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
            } catch (CalcException& exception) {
                std::cout << exception.what() << std::endl;
            } catch (std::exception& exception) {
                std::cout << std::format("Caught exception during program runtime\nwhat: {}", exception.what());
                exit(1);
            }
        }
    }
};
