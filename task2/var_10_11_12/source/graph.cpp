#include <fstream>

#include "graph.hpp"

namespace Alg {
    Graph::Graph(const std::string& filename)
    {
        read(filename);
    }

    bool Graph::read(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        int code = 0;

        file >> code;
        switch (code)
        {
        case ADJ_LIST:
            return readAdjList(file);
        case ADJ_MATRIX:
            return readAdjMatrix(file);
        default:
            return false;
        }

        return true;
    }

    bool Graph::readAdjMatrix(std::ifstream& file) {
        int vertexNumber = 0;

        file >> vertexNumber;
        this->vertexNumber = vertexNumber;
        adjMatrix.resize(vertexNumber);
        for (int row = 0; row < vertexNumber; row++) {
            adjMatrix[row].resize(vertexNumber);
            for (int col = 0; col < vertexNumber; col++) {
                int linksNumber;
                file >> linksNumber;
                adjMatrix[row][col] = linksNumber;
            }
        }
        matrixSet = true;
        return true;
    }

    bool Graph::readAdjList(std::ifstream& file) {
        int vertexNumber = 0;

        file >> vertexNumber;
        this->vertexNumber = vertexNumber;
        adjList.resize(vertexNumber);
        for (int i = 0; i < vertexNumber; i++) {
            int vertex, linkVertex;
            file >> vertex;
            while (file.peek() != '\n' && !file.eof()) {
                file >> linkVertex;
                adjList[vtoi(vertex)].pushSorted(vtoi(linkVertex));
            }
        }
        listSet = true;
        return true;
    }

    bool Graph::write(const std::string& filename, TypeCode as)
    {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        switch (as)
        {
        case Alg::Graph::ADJ_LIST:
            return writeAdjList(file);
        case Alg::Graph::ADJ_MATRIX:
            return writeAdjMatrix(file);
        default:
            return false;
            break;
        }
        return true;
    }

    bool Graph::writeAdjMatrix(std::ofstream& file) {
        file << ADJ_MATRIX << " " << vertexNumber << std::endl;

        if (!matrixSet) {
            asAdjMatrix();
        }

        for (int row = 0; row < vertexNumber; row++) {
            for (int col = 0; col < vertexNumber; col++) {
                file << adjMatrix[row][col] << " ";
            }
            file << std::endl;
        }
        return true;
    }

    bool Graph::writeAdjList(std::ofstream& file) {
        file << ADJ_LIST << " " << adjList.size() << std::endl;

        if (!listSet) {
            asAdjList();
        }

        for (int row = 0; row < vertexNumber; row++) {
            for (int i = 0; i < adjList[row].size(); i++) {
                file << itov(adjList[row][i]) << " ";
            }
            file << std::endl;
        }

        return true;
    }

    void Graph::clear(bool clearAdjList, bool clearAdjMatrix) {
        if (clearAdjList) {
            adjList.clear();
        }
        if (clearAdjMatrix) {
            adjMatrix.clear();
        }
    }

    const AdjacencyList& Graph::asAdjList() {
        if (!listSet) {
            adjList.clear();
            adjList.resize(adjMatrix.size());
            for (int row = 0; row < adjMatrix.size(); row++) {
                for (int col = 0; col < adjMatrix[row].size(); col++) {
                    size_t linksNum = adjMatrix[row][col];
                    for (int i = 0; i < linksNum; i++) {
                        adjList[row].pushBack(col);
                    }
                }
            }
            listSet = true;
        }

        return adjList;
    }

    const AdjacencyMatrix& Graph::asAdjMatrix() {
        if (!matrixSet) {
            adjMatrix.clear();
            adjMatrix.resize(adjList.size());
            for (int row = 0; row < adjList.size(); row++) {
                adjMatrix[row].resize(adjList.size());
                for (int col = 0; col < adjList.size(); col++) {
                    adjMatrix[row][col] = adjList[row].find(col);
                }
            }
            matrixSet = true;
        }

        return adjMatrix;
    }

    inline int Graph::vtoi(int v) const {
        return v - 1;
    }

    inline int Graph::itov(int i) const {
        return i + 1;
    }
}