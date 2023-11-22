#include "expert.hpp"

namespace Alg {

    void Expert::print(const std::string &what) {
        std::cout << what << std::endl;
    }

    std::string Expert::request(const std::string &what) {
        print(what);
        std::cout << "> ";
        std::string answer;
        answer = readLine();
        return answer;
    }

    bool Expert::parseAnswer(const std::string &answer) {
        return answer == "Yes" || answer == "yes" || answer == "y" || answer == "Y";
    }

    std::string Expert::readLine() {
        std::string response;
        std::getline(std::cin, response);
        return response;
    }

    Expert::Expert(const std::string &pathToDB) {
        root = nullptr;

        if (!pathToDB.empty()) {
            // #TODO: read expert tree from file
        }
    }

    void Expert::startGuessing() {
        print("Guess the word and I'll guess it!");
        print("All you have to do is answer yes/no to my questions!");

        std::string response;
        // Если дерево пустое
        if (root == nullptr) {
            readFirstFeatureAndAnswer();
            return;
        }

        QuestionTree *current = root;
        while (current != nullptr) {
            // Ответ "Да"
            if (parseAnswer(request(current->what + "?"))) {
                // Ответ "Да" на объект
                if (current->yes == nullptr) {
                    print("Yaaay, I'm smart after all!");
                    break;
                // Ответ "Да" на вопрос
                } else {
                    current = current->yes;
                }
            // Ответ "Нет" и при этом дерево закончилось
            } else if (current->no == nullptr) {
                readNewFeatureAndAnswer(current);
                break;
            // Ответ "Нет", но вопросы остались
            } else {
                current = current->no;
            }
        }
    }

    void Expert::readFirstFeatureAndAnswer() {
        // Просим ввести первую характеристику и соответствующий ей объект
        print("Looks like I don't know anything...");
        std::string answer = request("Would you like to teach me a little?");
        if (parseAnswer(answer)) {
            std::string name, feature;
            name = request("Enter the object name");
            feature = request("Describe the main feature of the " + name + " (Ex. \"Can swim\")");

            auto *answerNode = new QuestionTree(name, nullptr, nullptr);
            root = new QuestionTree(feature, answerNode, nullptr);
            print("Thanks! Now I'm ever smarter!");
        } else {
            print("Well, then... fine");
        }

    }

    void Expert::readNewFeatureAndAnswer(Alg::QuestionTree *parent) {
        print("Sorry, looks like I don't know what is it...");
        std::string answer = request("Would you like to teach me a little?");
        if (parseAnswer(answer)) {
            std::string name, feature;
            name = request("Enter the object name");
            feature = request("Describe the main feature of the " + name + " (Ex. \"Can swim\")");
            parent->addNo(feature, name);
            print("Thanks! Now I'm ever smarter!");
        } else {
            print("Well, then... fine");
        }
    }

} // Alg