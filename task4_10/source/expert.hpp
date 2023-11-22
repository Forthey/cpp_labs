#ifndef TASK3_6_EXPERT_H
#define TASK3_6_EXPERT_H

#include <iostream>
#include "question_tree.hpp"

namespace Alg {

    class Expert {
        QuestionTree *root;

        static std::string request(const std::string &what);
        static void print(const std::string &what);
        static bool parseAnswer(const std::string &answer);
        static std::string readLine();

        void readFirstFeatureAndAnswer();
        void readNewFeatureAndAnswer(QuestionTree *parent);
    public:
        Expert(const std::string &pathToDB = "");

        void startGuessing();
    };

} // Alg
#endif //TASK3_6_EXPERT_H
