#include "graph.hpp"

int main() {
    Alg::Graph graph;
    if (!graph.findPath()) {
        std::cout << "Path not found" << std::endl;
    } else {
        std::cout << "Path has been found" << std::endl;
    }
    return 0;
}