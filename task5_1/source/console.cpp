#include "console.hpp"

void Console::print(const std::string &what) {
    std::cout << what << std::endl;
}

std::string Console::request(const std::string &what) {
    if(!what.empty()) {
        print(what);
    }
    std::cout << "> ";
    std::string answer;
    answer = readLine();
    return answer;
}

Console::Answer Console::parseAnswer(const std::string &answer) {
    if (answer == "Exit" || answer == "exit" || answer == "q" || answer == "Q") {
        return Exit;
    }
    if (answer == "Load" || answer == "load" || answer == "l" || answer == "L") {
        return Load;
    }
    if (answer == "Console" || answer == "console" || answer == "cs" || answer == "c") {
        return Cons;
    }
    if (answer == "Display" || answer == "display" || answer == "print" || answer == "p") {
        return Display;
    }
    if (answer == "Tree" || answer == "tree" || answer == "t" || answer == "T") {
        return Tree;
    }
    if (answer == "Help" || answer == "help" || answer == "h" || answer == "H") {
        return Help;
    }
    return Hz;
}

std::string Console::readLine() {
    std::string response;
    std::cin >> response;
    return response;
}