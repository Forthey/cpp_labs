#include <iostream>
#include "graph.hpp"

#pragma execution_character_set("utf-8")

int main() {
    //std::locale::global(std::locale("ru-RU.utf-8"));
    Alg::Graph graph;
    if (graph.read("graphs/graph_as_list.graph"))
        std::cout << "Finally..." << std::endl;
    else
        std::cout << "Nope" << std::endl;
    graph.write("graphs/graph_as_matrix.graph", Alg::Graph::ADJ_MATRIX);
    return 0;
}