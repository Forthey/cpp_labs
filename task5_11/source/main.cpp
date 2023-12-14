#include "segment_tree.hpp"

std::string getCommands() {
    return "add - add new segment\n"
           "delete - delete existing segment\n"
           "display - display segments\n"
           "intersect - check intersection\n"
           "save - save segments\n"
           "load - load segments from file\n"
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
    Alg::SegmentTree segmentTree;
    std::pair<int, int> segment;

    Console::print(getCommands());
    while (!endResponse) {
        response = Console::request("");

        switch(Console::parseAnswer(response)) {
            case Console::Exit:
                Console::print("Exiting...");
                endResponse = true;
                break;
            case Console::Add:
                segment = requestSegment();
                segmentTree.add(segment.first, segment.second);
                Console::print("Segment has been added");
                break;
            case Console::Delete:
                segment = requestSegment();
                segmentTree.remove(segment.first, segment.second);
                Console::print("Segment has been removed");
                break;
            case Console::Display:
                segmentTree.displayRotated();
                break;
            case Console::Intersect:
                segment = requestSegment();
                segmentTree.allIntersects(segment.first, segment.second);
            case Console::Help:
                Console::print(getCommands());
                break;
            case Console::Save:
                // #TODO: Save
                break;
            case Console::Load:
                // #TODO: Load
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
