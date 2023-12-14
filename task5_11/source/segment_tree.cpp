//
// Created by 0Fort on 14.12.2023.
//
#include <queue>
#include <map>
#include <cmath>
#include <iomanip>
#include "segment_tree.hpp"

namespace Alg {
    SegmentTree::SegmentTree() {
        root = nullptr;
        segmentsNumber = 0;
    }


    bool SegmentTree::add(int a, int b) {
        return add(a, b, b);
    }
    bool SegmentTree::add(int a, int b, int splitPoint) {
        Node *newSegment = new Node(a, b, splitPoint, nullptr, nullptr);

        // Если компу плохо и я написал noexcept
        if (newSegment == nullptr) {
            return false;
        }

        // Увеличиваем число отрезков, т.к. потом 100% добавим его куда-нибудь
        segmentsNumber++;

        // Если отрезков нет
        if (root == nullptr) {
            root = newSegment;
            return true;
        }

        // Итератор по дереву
        Node *iterator = root;
        // На самом деле условие выхода для красоты
        while (iterator != nullptr) {
            // Если надо идти вправо...
            if (newSegment->b > iterator->splitPoint) {
                // ...а идти дальше некуда - добавляем вправо и выходим
                if (iterator->right == nullptr) {
                    iterator->right = newSegment;
                    return true;
                }
                // ...идём вправо
                iterator = iterator->right;
            } else { // Если надо идти влево...
                // ...а идти дальше некуда - добавляем влево и выходим
                if (iterator->left == nullptr) {
                    iterator->left = newSegment;
                    return true;
                }
                // ...идём влево
                iterator = iterator->left;
            }
        }
        return false;
    }

    void SegmentTree::addToVeryLeft(Node *where, Node *what) {
        if (where == nullptr) {
            return;
        }
        while (where->left != nullptr) {
            where = where->left;
        }
        where->left = what;
    }

    bool SegmentTree::remove(int a, int b) {
        // Итератор по дереву и предыдущий отрезок
        Node *iterator = root, *previous = nullptr;

        // Флаг последнего прохода
        bool wentRight = false;
        while (iterator != nullptr) {
            // Если мы нашли отрезок
            if (iterator->a == a && iterator->b == b) {
                // Убираем левое поддерево в левую часть правого
                addToVeryLeft(iterator->right, iterator->left);
                // Меняем указатель у родителя на правое поддерево отрезка
                if (previous != nullptr) {
                    if (wentRight) {
                        previous->right = iterator->right;
                    } else {
                        previous->left = iterator->right;
                    }
                } else {
                    root = root->right;
                }
                segmentsNumber--;
                delete iterator;
                return true;
            }

            // Запоминаем предыдущий
            previous = iterator;
            // Если надо идти вправо...
            if (b > iterator->splitPoint) {
                // ...а идти дальше некуда - то отрезка нету :(
                if (iterator->right == nullptr) {
                    return false;
                }
                // ...идём вправо
                iterator = iterator->right;
                wentRight = true;
            } else { // Если надо идти влево...
                // ...а идти дальше некуда - то отрезка нету :(
                if (iterator->left == nullptr) {
                    return false;
                }
                // ...идём влево
                iterator = iterator->left;
                wentRight = false;
            }

        }
        return false;
    }

    bool SegmentTree::find(int a, int b) {
        // Итератор по дереву
        Node *iterator = root;

        while (iterator != nullptr) {
            // Если мы нашли отрезок
            if (iterator->a == a && iterator->b == b) {
                return true;
            }

            // Если надо идти вправо...
            if (b > iterator->splitPoint) {
                // ...а идти дальше некуда - то отрезка нету :(
                if (iterator->right == nullptr) {
                    return false;
                }
                // ...идём вправо
                iterator = iterator->right;
            } else { // Если надо идти влево...
                // ...а идти дальше некуда - то отрезка нету :(
                if (iterator->left == nullptr) {
                    return false;
                }
                // ...идём влево
                iterator = iterator->left;
            }

        }
        return false;
    }


    void SegmentTree::clear() {
        clearRec(root);
    }

    void SegmentTree::clearRec(SegmentTree::Node *node) {
        if (node == nullptr) {
            return;
        }
        clearRec(node->left);
        clearRec(node->right);
        delete node;
    }

    SegmentTree::~SegmentTree() {
        clear();
    }

    // #TODO: хз как, но поправить вывод "неровного" дерева
    void SegmentTree::display(std::ostream &out) {
        if (root == nullptr) {
            out << "<empty list>" << std::endl;
            return;
        }

        // Обход в ширину
        std::queue<Node *> nodes;
        std::map<Node *, bool> visitedNodes;
        int depth = 0, numCnt = 0;

        nodes.push(root);
        while (!nodes.empty()) {
            Node *node = nodes.front();
            nodes.pop();
            if (visitedNodes.count(node) == 0) {
                visitedNodes[node] = true;
                for (int i = 0; i < segmentsNumber - depth; i++) {
                    out << "\t";
                }
                out << "[" << node->a << "; " << node->b << "]\t";
                if (node->left != nullptr) {
                    nodes.push(node->left);
                }
                if (node->right != nullptr) {
                    nodes.push(node->right);
                }
            }


            if (numCnt == pow(2, depth) || depth == 0) {
                depth++;
                out << std::endl;
            }
            numCnt++;
        }
    }

    void SegmentTree::displayRotated(std::ostream &out) {
        displayRec(out, root, 0);
    }

    void SegmentTree::displayRec(std::ostream &out, SegmentTree::Node *node, int depth) {
        if (node == nullptr) {
            out << std::endl;
            return;
        }
        displayRec(out, node->right, depth + 1);
        for (int i = 0; i < depth; i++) {
            out << std::setw(11) << "";
        }
        std::string segment = "[" + std::to_string(node->a) + "; " + std::to_string(node->b) + "]";
        out << std::setw(11) << segment;
        displayRec(out, node->left, depth + 1);
    }

    int SegmentTree::allIntersects(int a, int b, std::ostream &out) {
        return allIntersectsRec(root, a, b, out);
    }

    int SegmentTree::allIntersectsRec(Node *node, int a, int b, std::ostream &out) {
        if (node == nullptr) {
            return 0;
        }
        int thisIntersect = 0;
        if ((a - node->b) * (node->a - b) > 0) {
            out << "[" << node->a << "; " << node->b << "]" << std::endl;
            thisIntersect = 1;
        }

        if (node->splitPoint < a) {
            return thisIntersect + allIntersectsRec(node->right, a, b, out);
        }

        return thisIntersect + allIntersectsRec(node->right, a, b, out) + allIntersectsRec(node->left, a, b, out);
    }


} // Alg