
#include "graph.hpp"

namespace Alg {
    Graph::Graph(const std::string &filename) {

    }

    std::string Graph::findPathRec(AdjMatrix &mask, int current, int to, int lengthCapacity) {
        for (int vertex = 0; vertex < mask[current].size(); vertex++) {
            // Если пути нет или это ребро уже проходили
            if (mask[current][vertex] == 0)
                continue;
            // Проверям, может мы нашли путь не меньше K
            if (lengthCapacity <= 0 && vertex == to)
                return std::to_string(vertex);
            // Помечаем, что были на ребре current-vertex (убираем его из маски)
            mask[current][vertex] = 0;
            // Переходим в вершину vertex и смотрим, есть ли путь
            std::string path = findPathRec(mask, vertex, to, lengthCapacity - 1);
            // Пути нет
            if (path.empty()) {
                return "";
            }
            // Путь есть, ура
            return std::to_string(vertex) + path;
        }
        // Если зашли в тупик (все ребра пройдены)
        return "";
    }

    void Graph::findPath(int from, int to, int minLength, const std::string &filename) {
        AdjMatrix mask = graph;
        std::string path = findPathRec(mask, from, to, minLength);
    }
}