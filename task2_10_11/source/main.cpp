#include <iostream>
#include "graph.hpp"

void graph_menu() {
    Alg::Graph graph;
    std::string inputFile, outputFile;
    const std::string srcFolder = "graphs/";
    Alg::Graph::TypeCode saveType;

    std::cout << "Enter the path to the file" << std::endl;
    std::cout << "> ";
    std::cin >> inputFile;

    switch (graph.read(srcFolder + inputFile)) {
        case Alg::Graph::NONE:
            std::cout << "File doesn't exist..." << std::endl;
            return;
        case Alg::Graph::ADJ_MATRIX:
            std::cout << "Graph was read as adjacency matrix and will be saved as adjacency list" << std::endl;
            saveType = Alg::Graph::ADJ_LIST;
            break;
        case Alg::Graph::ADJ_LIST:
            std::cout << "Graph was read as adjacency list and will be saved as adjacency matrix" << std::endl;
            saveType = Alg::Graph::ADJ_MATRIX;
            break;
    }

    std::cout << "Enter the path to the output file" << std::endl;
    std::cout << "> ";
    std::cin >> outputFile;
    std::cout << "Writing the graph into the file..." << std::endl;
    if (graph.write(srcFolder + outputFile, saveType)) {
        std::cout << "Graph has been saved in " << outputFile << std::endl;
    } else {
        std::cout << "Some error has happened. Please, try again" << std::endl;
    }
}

void menu() {
    std::cout << "begin - start converting" << std::endl;
    std::cout << "help - list all commands" << std::endl;
    std::cout << "exit - exit program" << std::endl;
}

void start() {
    std::string response;
    bool open = true;

    menu();
    while (open) {
        std::cout << "> ";
        std::cin >> response;

        if (response == "begin") {
            graph_menu();
        } else if (response == "exit") {
            open = false;
        } else if (response == "help") {
            menu();
        } else {
            std::cout << "Wrong input, please try again (or use 'help' command)" << std::endl;
        }
    }
}

int main() {
    start();
    return 0;
}