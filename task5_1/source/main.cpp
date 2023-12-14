#include "tree.hpp"

std::string getCommands() {
    return "load - build from file\n"
           "console - build from console\n"
           "display - display table\n"
           "tree - display tree\n"
           "exit - exit program\n"
           "help - list all commands";
}

std::pair<int, int> requestSegment() {
    int a, b;
    Console::print("Enter a and b separated by space");
    std::cin >> a >> b;
    return {a, b};
}

void menu() {
    bool endResponse = false;
    std::string response;
    Alg::Tree tree;
    std::pair<int, int> segment;

    Console::print(getCommands());
    while (!endResponse) {
        response = Console::request("");

        switch(Console::parseAnswer(response)) {
            case Console::Exit:
                Console::print("Exiting...");
                endResponse = true;
                break;
            case Console::Load:
                if (tree.buildFromFile(Console::request("Enter filename"))) {
                    Console::print("The table has been built");
                } else {
                    Console::print("Sorry, the file doesn't exist");
                }
                break;
            case Console::Cons:
                Console::print("Double 'Enter' will terminate input");
                tree.buildFromConsole();
                break;
            case Console::Display:
                tree.displayTable();
                break;
            case Console::Tree:
                tree.displayTree();
                break;
            case Console::Help:
                Console::print(getCommands());
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
