#ifndef TASK5_1_TREE_H
#define TASK5_1_TREE_H
#include <string>
#include <list>
#include <fstream>
#include "console.hpp"

namespace Alg {

    class Tree {
        class Node {
        public:
            std::string word;
            std::list<size_t> rows;
            Node *left, *right;

            explicit Node(std::string word, Node *left, Node* right) : word(std::move(word)), left(left), right(right) {}
        } *root;
        int wordsNumber;

        bool add(const std::string &word, size_t row);

        void clearRec(Node *node);
        void displayRec(std::ostream &out, Node *node, int depth);
        void displayTableRec(std::ostream &out, Node *node);
    public:
        Tree();
        bool buildFromFile(const std::string &filename);
        void buildFromConsole();

        void displayTree(std::ostream &out = std::cout);
        void displayTable(std::ostream &out = std::cout);

        void clear();
        ~Tree();
    };

} // Alg

#endif //TASK5_1_TREE_H
