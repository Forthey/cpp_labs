#ifndef TASK3_6_QUESTIONTREE_H
#define TASK3_6_QUESTIONTREE_H
#include <string>

namespace Alg {

    class QuestionTree {
    public:
        std::string what;
        QuestionTree *yes = nullptr, *no = nullptr;

        QuestionTree(std::string &what, QuestionTree *yes, QuestionTree *no) : what(what), yes(yes), no(no) {}
        //~QuestionTree();

        void addNo(std::string &question, std::string &answer);
        void addNo(std::string &answer);
        void clear();
    };

} // Alg

#endif //TASK3_6_QUESTIONTREE_H
