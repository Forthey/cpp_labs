#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace Alg {
    typedef std::vector<std::vector<int>> AdjMatrix;

    class Graph {
        AdjMatrix graph;

        std::string findPathRec(AdjMatrix &mask, int current, int to, int lengthCapacity);
        std::string findPath(int from, int to, int maxLength);

        int vtoi(int v);
        int itov(int i);
    public:
        bool findPath(const std::string &inFilename = "input.txt", const std::string &outFilename = "output.txt");
    };
}