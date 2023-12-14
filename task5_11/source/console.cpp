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
    if (answer == "Add" || answer == "add" || answer == "a" || answer == "A") {
        return Add;
    }
    if (answer == "Delete" || answer == "delete" || answer == "d" || answer == "D") {
        return Delete;
    }
    if (answer == "Display" || answer == "display" || answer == "print" || answer == "p") {
        return Display;
    }
    if (answer == "Intersect" || answer == "intersect" || answer == "i" || answer == "int") {
        return Intersect;
    }
    if (answer == "Load" || answer == "load" || answer == "l" || answer == "L") {
        return Load;
    }
    if (answer == "Save" || answer == "save" || answer == "s" || answer == "S") {
        return Save;
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