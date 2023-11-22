#include "question_tree.hpp"

namespace Alg {
    void QuestionTree::addNo(std::string &question, std::string &answer) {
        // Это ответ
        if (yes == nullptr) {
            yes = new QuestionTree(answer, nullptr, nullptr);
            no = new QuestionTree(what, nullptr, nullptr);
            what = question;
        } else {
            auto *answerNode = new QuestionTree(answer, nullptr, nullptr);
            no = new QuestionTree(question, answerNode, nullptr);
        }
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

    QuestionTree::~QuestionTree() {
        clear();
    }
} // Alg