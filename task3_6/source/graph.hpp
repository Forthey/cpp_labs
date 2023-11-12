#pragma once
#include <vector>
#include <string>

namespace Alg {
    typedef std::vector<std::vector<int>> AdjMatrix;

    class Graph {
        AdjMatrix graph;

        std::string findPathRec(AdjMatrix &mask, int current, int to, int lengthCapacity);
    public:
        Graph(const std::string &filename = "input.txt");

        void findPath(int from, int to, int maxLength, const std::string &filename = "output.txt");
    };
}