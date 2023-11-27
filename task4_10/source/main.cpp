#include "expert.hpp"

std::string getCommands() {
    return "start - start guessing\n"
           "save - save expert to file\n"
           "load - load expert from file\n"
           "exit - exit program\n"
           "help - list all commands";
}

void menu() {
    bool endResponse = false;
    std::string response;
    Alg::Expert expert;

    Console::print(getCommands());
    while (!endResponse) {
        response = Console::request("");

        switch(Console::parseAnswer(response)) {
            case Console::Exit:
                endResponse = true;
                break;
            case Console::Start:
                expert.startGuessing();
                break;
            case Console::Help:
                Console::print(getCommands());
                break;
            case Console::Save:
                expert.save(Console::request("Enter file name"));
                break;
            case Console::Load:
                expert.load(Console::request("Enter file name"));
                break;
            case Console::Hz:
            default:
                Console::print("Unknown command... (write 'help' to list all commands)");
        }
    }
}

int main() {
    menu();
    return 0;
}
