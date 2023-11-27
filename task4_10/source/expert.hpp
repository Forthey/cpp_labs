#ifndef TASK3_6_EXPERT_H
#define TASK3_6_EXPERT_H

#include "console.hpp"
#include "question_tree.hpp"

namespace Alg {

    class Expert {
        QuestionTree *root;

        void readFirstFeatureAndAnswer();
        void readNewFeatureAndAnswer(QuestionTree *parent);

        void readRec(std::ifstream &file, QuestionTree *iter);
        void saveRec(std::ofstream &file, QuestionTree *iter);
    public:
        explicit Expert(const std::string &path = "");

        bool read(const std::string &path);
        bool save(const std::string &path);
        void clear();

        void startGuessing();

        ~Expert();
    };

} // Alg
#endif //TASK3_6_EXPERT_H
