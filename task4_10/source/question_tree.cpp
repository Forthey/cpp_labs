#include "question_tree.hpp"

namespace Alg {
    void QuestionTree::addYes(std::string &question, std::string &answer) {
        QuestionTree *answerNode = new QuestionTree(answer, nullptr, nullptr); 
        yes = new QuestionTree(question, answerNode, nullptr);
    }

    void QuestionTree::addNo(std::string &question, std::string &answer) {
        QuestionTree *answerNode = new QuestionTree(answer, nullptr, nullptr);
        no = new QuestionTree(question, answerNode, nullptr);
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

    const QuestionTree *QuestionTree::getYes() {
        return yes;
    }

    const QuestionTree *QuestionTree::getNo() {
        return no;
    }
} // Alg