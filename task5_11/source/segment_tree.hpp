#ifndef TASK5_11_SEGMENTTREE_H
#define TASK5_11_SEGMENTTREE_H
#include <string>
#include <ostream>
#include "console.hpp"

namespace Alg {

    class SegmentTree {
        class Node {
        public:
            int a, b;
            int splitPoint;
            Node *left, *right;

            explicit Node(int a, int b, int splitPoint, Node *left, Node* right) : a(a), b(b), splitPoint(splitPoint), left(left), right(right) {}
        } *root;
        int segmentsNumber;

        void clearRec(Node *node);
        void displayRec(std::ostream &out, Node *node, int depth);
        int allIntersectsRec(Node *node, int a, int b, std::ostream &out);

        void addToVeryLeft(Node *where, Node *what);
    public:
        SegmentTree();
        bool add(int a, int b);
        bool add(int a, int b, int splitPoint);
        bool remove(int a, int b);
        bool find(int a, int b);
        int allIntersects(int a, int b, std::ostream &out = std::cout);

        void displayRotated(std::ostream &out = std::cout);
        void display(std::ostream &out =  std::cout);

        //  #TODO: мб убрать рекурсию из очистки
        void clear();
        ~SegmentTree();
    };

} // Alg

#endif //TASK5_11_SEGMENTTREE_H
