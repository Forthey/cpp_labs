#include <fstream>
#include "graph.hpp"

namespace Alg {
    std::string Graph::findPathRec(AdjMatrix &mask, int current, int to, int lengthCapacity) {
        for (int vertex = 0; vertex < mask[current].size(); vertex++) {
            // Если пути нет или это ребро уже проходили
            if (mask[current][vertex] == 0)
                continue;
            // Проверям, может мы нашли путь не меньше K
            if (lengthCapacity <= 1 && vertex == to)
                return std::to_string(itov(vertex));
            // Помечаем, что были на ребре current-vertex (убираем его из маски)
            int oldValue = mask[current][vertex];
            mask[current][vertex] = 0;
            if (current != vertex) {
                mask[vertex][current] = 0;
            }
            // Переходим в вершину vertex и смотрим, есть ли путь
            std::string path = findPathRec(mask, vertex, to, lengthCapacity - 1);
            // Пути нет
            if (path.empty()) {
                // Делаем вид, что мы по этому пути не ходили
                mask[current][vertex] = oldValue;
                mask[vertex][current] = oldValue;
                continue;
            }
            // Путь есть, ура
            return std::to_string(itov(vertex)) + " " + path;
        }
        // Если зашли в тупик (все ребра пройдены)
        return "";
    }

    std::string Graph::findPath(int from, int to, int minLength) {
        AdjMatrix mask = graph;
        std::string path = findPathRec(mask, from, to, minLength);
        if (path.empty()) {
            return "0";
        }
        return std::to_string(itov(from)) + " " + path;
    }

    bool Graph::findPath(const std::string &inFilename, const std::string &outFilename) {
        std::ifstream fileIn(inFilename);
        if (!fileIn.is_open()) {
            return false;
        }

        int size, from, to, minLength;
        fileIn >> size >> from >> to >> minLength;
        graph.resize(size);
        for (auto& row : graph) {
            row.resize(size);
        }

        int vertex1, vertex2;
        while (!fileIn.eof()) {
            fileIn >> vertex1 >> vertex2;
            vertex1 = vtoi(vertex1);
            vertex2 = vtoi(vertex2);
            graph[vertex1][vertex2]++;
            if (vertex1 != vertex2) {
                graph[vertex2][vertex1]++;
            }
        }
        fileIn.close();

        std::string path = findPath(vtoi(from), vtoi(to), minLength);
        graph.clear();

        std::ofstream fileOut(outFilename);
        if (!fileOut.is_open()) {
            return false;
        }
        fileOut << path;
        fileOut.close();

        return path != "0";
    }

    inline int Graph::vtoi(int v) {
        return v - 1;
    }

    inline int Graph::itov(int i) {
        return i + 1;
    }
}