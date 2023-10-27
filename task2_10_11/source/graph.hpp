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

        static int vtoi(int v) ;
        static int itov(int i) ;

        void readAdjMatrix(std::ifstream& file);
        void readAdjList(std::ifstream& file);
        void writeAdjMatrix(std::ofstream& file);
        void writeAdjList(std::ofstream& file);
    public:
        enum TypeCode {
            NONE = -1,
            ADJ_LIST = 0,
            ADJ_MATRIX = 1
        };

        Graph() = default;
        Graph(const std::string &filename);

        TypeCode read(const std::string& filename);
        bool write(const std::string& filename, TypeCode as = ADJ_LIST);

        const AdjacencyList& asAdjList();
        const AdjacencyMatrix& asAdjMatrix();
    };
}

