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
    if (answer == "Yes" || answer == "yes" || answer == "y" || answer == "Y") {
        return Yes;
    }
    if (answer == "Load" || answer == "load" || answer == "l" || answer == "L") {
        return Load;
    }
    if (answer == "Save" || answer == "save" || answer == "s" || answer == "S") {
        return Save;
    }
    if (answer == "Start" || answer == "start" || answer == "g" || answer == "G") {
        return Start;
    }
    if (answer == "Help" || answer == "help" || answer == "h" || answer == "H") {
        return Help;
    }
    return Hz;
}

std::string Console::readLine() {
    std::string response;
    std::getline(std::cin, response);
    return response;
}