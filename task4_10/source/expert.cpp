#include "expert.hpp"

namespace Alg {

    void Expert::line(const std::string &what) {
        std::cout << what << std::endl;
    }

    void Expert::request(const std::string &what) {
        line(what);
        std::cout << "> ";
    }

    bool Expert::readAnswer() {
        std::string response;
        std::cin >> response;
        return response == "Yes" || response == "yes" || response == "y" || response == "Y";
    }

    Expert::Expert(const std::string &pathToDB) {
        root = nullptr;

        if (!pathToDB.empty()) {
            // #TODO: read expert tree from file
        }
    }

    void Expert::startGuessing() {
        std::string response;
        // Если дерево пустое
        if (root == nullptr) {
            readFirstFeatureAndAnswer();
        }
        QuestionTree *current = root;
    }

    void Expert::readFirstFeatureAndAnswer() {
        // Просим ввести первую характеристику и соответствующий ей объект
        line("Looks like The Expert doesn't know anything...");
        request("Would you like to teach it a little thing?");
        if (readAnswer()) {
            std::string name, feature;
            request("Enter the object name");
            std::cin >> name;
            request("Describe the main feature of the " + name);
            std::cin >> feature;

            QuestionTree *answerNode = new QuestionTree(name, nullptr, nullptr);
            root = new QuestionTree(feature, answerNode, nullptr);
        }

    }

    void Expert::readNewFeatureAndAnswer(Alg::QuestionTree *parent) {
    }

} // Alg