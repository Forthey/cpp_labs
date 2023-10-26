#include <iostream>
#include "graph.hpp"

#pragma execution_character_set("utf-8")

int main() {
    std::locale::global(std::locale("ru-RU.utf-8"));
    Alg::Graph graph("graphs/graph_as_list.graph");
    graph.write("graphs/graph_as_matrix.graph", Alg::Graph::ADJ_MATRIX);
    return 0;
}