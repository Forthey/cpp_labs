#ifndef TASK3_6_EXPERT_H
#define TASK3_6_EXPERT_H

#include <iostream>
#include "question_tree.hpp"

namespace Alg {

    class Expert {
        QuestionTree *root;

        static void request(const std::string &what);
        static void line(const std::string &what);
        static bool readAnswer();

        void readFirstFeatureAndAnswer();
        void readNewFeatureAndAnswer(QuestionTree *parent);
    public:
        Expert(const std::string &pathToDB = "");

        void startGuessing();
    };

} // Alg
#endif //TASK3_6_EXPERT_H
