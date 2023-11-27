#ifndef TASK3_6_EXPERT_H
#define TASK3_6_EXPERT_H

#include "console.hpp"
#include "question_tree.hpp"

namespace Alg {

    class Expert {
        QuestionTree *root;

        void readFirstFeatureAndAnswer();
        void readNewFeatureAndAnswer(QuestionTree *parent);
    public:
        Expert(const std::string &pathToDB = "");

        void startGuessing();
    };

} // Alg
#endif //TASK3_6_EXPERT_H
