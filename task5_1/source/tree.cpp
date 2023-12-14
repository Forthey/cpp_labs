//
// Created by 0Fort on 14.12.2023.
//
#include <map>
#include <cmath>
#include <iomanip>
#include "tree.hpp"

namespace Alg {
    Tree::Tree() {
        root = nullptr;
        wordsNumber = 0;
    }

    bool Tree::add(const std::string &word, size_t row) {
        // Если отрезков нет
        if (root == nullptr) {
            wordsNumber++;
            root = new Node(word, nullptr, nullptr);
            // Если компу плохо и я написал noexcept
            if (root == nullptr) {
                return false;
            }
            root->rows.push_back(row);
            return true;
        }

        // Итератор по дереву
        Node *iterator = root;
        // На самом деле условие выхода для красоты
        while (iterator != nullptr) {
            // > 0 если word > iterator->word...
            int compare = word.compare(iterator->word);
            // Если нашли слово
            if (compare == 0) {
                iterator->rows.push_back(row);
                return true;
            }
            // Если надо идти вправо...
            if (compare > 0) {
                // ...а идти дальше некуда - добавляем вправо и выходим
                if (iterator->right == nullptr) {
                    iterator->right = new Node(word, nullptr, nullptr);
                    // Если компу плохо и я написал noexcept
                    if (root == nullptr) {
                        return false;
                    }
                    wordsNumber++;
                    iterator->right->rows.push_back(row);
                    return true;
                }
                // ...идём вправо
                iterator = iterator->right;
            } else { // Если надо идти влево...
                // ...а идти дальше некуда - добавляем влево и выходим
                if (iterator->left == nullptr) {
                    iterator->left =  new Node(word, nullptr, nullptr);
                    // Если компу плохо и я написал noexcept
                    if (root == nullptr) {
                        return false;
                    }
                    wordsNumber++;
                    iterator->left->rows.push_back(row);
                    return true;
                }
                // ...идём влево
                iterator = iterator->left;
            }
        }
        return false;
    }

    bool Tree::buildFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        std::string row, word;
        int rowNumber = 1;
        while(std::getline(file, row)) {
            std::istringstream iss(row);

            while (iss >> word) {
                add(word, rowNumber);
            }
            rowNumber++;
        }

        return true;
    }

    void Tree::buildFromConsole() {
        std::string row, word;
        int rowNumber = 1;
        do {
            std::getline(std::cin, row);
            std::istringstream iss(row);
            while (!(iss >> word)) {
                add(word, rowNumber);
            }
            rowNumber++;
        } while(!row.empty());
    }

    void Tree::displayTree(std::ostream &out) {
        displayRec(out, root, 0);
    }

    void Tree::displayRec(std::ostream &out, Tree::Node *node, int depth) {
        if (node == nullptr) {
            out << std::endl;
            return;
        }
        displayRec(out, node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            out << std::setw(15) << "";
        }
        out << std::setw(15) << node->word;
        displayRec(out, node->left, depth + 1);
    }

    void Tree::displayTable(std::ostream &out) {
        displayTableRec(out, root);
    }


    void Tree::displayTableRec(std::ostream &out, Tree::Node *node) {
        if (node == nullptr) {
            return;
        }
        displayTableRec(out, node->left);
        out << std::setw(15) << node->word << " |";
        for (size_t &row : node->rows) {
            out << std::setw(3) << row;
        }
        out << std::endl;
        displayTableRec(out, node->right);
    }


    void Tree::clear() {
        clearRec(root);
    }

    void Tree::clearRec(Tree::Node *node) {
        if (node == nullptr) {
            return;
        }
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

    Tree::~Tree() {
        clear();
    }

} // Alg