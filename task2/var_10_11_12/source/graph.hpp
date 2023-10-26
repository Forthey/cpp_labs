#pragma once
#include "list.hpp"

namespace Alg {
    typedef List<List<int>> AdjacencyMatrix;
    typedef List<List<int>> AdjacencyList;
    class Graph {
        AdjacencyList adjList;
        AdjacencyMatrix adjMatrix;
        bool listSet = false;
        bool matrixSet = false;
        int vertexNumber = 0;

        int vtoi(int v) const;
        int itov(int i) const;

        bool readAdjMatrix(std::ifstream& file);
        bool readAdjList(std::ifstream& file);
        bool writeAdjMatrix(std::ofstream& file);
        bool writeAdjList(std::ofstream& file);
    public:
        enum TypeCode {
            ADJ_LIST = 0,
            ADJ_MATRIX = 1
        };

        Graph() = default;
        Graph(const std::string &filename);

        bool read(const std::string& filename);
        bool write(const std::string& filename, TypeCode as = ADJ_LIST);

        void clear(bool clearAdjList = true, bool clearAdjMatrix = true);

        const AdjacencyList& asAdjList();
        const AdjacencyMatrix& asAdjMatrix();
    };
}

