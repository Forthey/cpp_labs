#include "expert.hpp"

std::string getCommands() {
    return "start - start guessing\n"
           "exit - exit program\n"
           "help - list all commands";
}

void menu() {
    bool endResponse = false;
    std::string response;
    Alg::Expert expert;

    while (!endResponse) {
        response = Console::request("");

        if (response == "exit") {
            endResponse = true;
        } else if (response == "start") {
            expert.startGuessing();
        } else if (response == "help") {
            Console::print(getCommands());
        } else {
            Console::print("Unknown command... (write 'help' to list all commands)");
        }
    }
}

int main() {
    menu();
    return 0;
}
