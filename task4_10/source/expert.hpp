#ifndef TASK3_6_EXPERT_H
#define TASK3_6_EXPERT_H
#include <string>
#include <iostream>

class Expert {
    class ExpertTree {
    public:
        ExpertTree(std::string &what, ExpertTree *yes, ExpertTree *no) : what(what), yes(yes), no(no) {}

        std::string what;
        ExpertTree *yes, *no;
    } *expertTree;

public:
    Expert(const std::string &pathToDB = "");

    void startGuessing();
};

#endif //TASK3_6_EXPERT_H
