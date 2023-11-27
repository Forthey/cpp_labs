#include "question_tree.hpp"

namespace Alg {
    void QuestionTree::addNo(std::string &question, std::string &answer) {
        delete yes;
        delete no;

        yes = new QuestionTree(answer, nullptr, nullptr);
        no = new QuestionTree(what, nullptr, nullptr);
        what = question;
    }

    void QuestionTree::addNo(std::string &answer) {
        delete no;

        no = new QuestionTree(answer, nullptr, nullptr);
    }

    void QuestionTree::clear() {
        if (yes != nullptr) {
            yes->clear();
            delete yes;
        }
        if (no != nullptr) {
            no->clear();
            delete no;
        }
    }

//    QuestionTree::~QuestionTree() {
//        clear();
//    }
} // Alg