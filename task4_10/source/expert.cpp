#include "expert.hpp"

namespace Alg {
    Expert::Expert(const std::string &pathToDB) {
        root = nullptr;

        if (!pathToDB.empty()) {
            // #TODO: read expert tree from file
        }
    }

    void Expert::startGuessing() {
        Console::print("Guess the word and I'll guess it!");
        Console::print("All you have to do is answer yes/no to my questions!");

        std::string response;
        // Если дерево пустое
        if (root == nullptr) {
            readFirstFeatureAndAnswer();
            return;
        }

        QuestionTree *current = root;
        while (current != nullptr) {
            // Ответ "Да"
            if (Console::parseAnswer(Console::request(current->what + "?"))) {
                // Ответ "Да" на объект
                if (current->yes == nullptr) {
                    Console::print("Yaaay, I'm smart after all!");
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
        Console::print("Looks like I don't know anything...");
        std::string answer = Console::request("Would you like to teach me a little?");
        if (Console::parseAnswer(answer)) {
            std::string name, feature;
            name = Console::request("Enter the object name");
            feature = Console::request("Describe the main feature of the " + name + " (Ex. \"Can swim\")");

            auto *answerNode = new QuestionTree(name, nullptr, nullptr);
            root = new QuestionTree(feature, answerNode, nullptr);
            Console::print("Thanks! Now I'm ever smarter!");
        } else {
            Console::print("Well, then... fine");
        }

    }

    void Expert::readNewFeatureAndAnswer(Alg::QuestionTree *parent) {
        Console::print("Sorry, looks like I don't know what is it...");
        std::string answer = Console::request("Would you like to teach me a little?");
        if (Console::parseAnswer(answer)) {
            std::string name, feature;
            name = Console::request("Enter the object name");
            feature = Console::request("Describe the main feature of the " + name + " (Ex. \"Can swim\")");
            parent->addNo(feature, name);
            Console::print("Thanks! Now I'm ever smarter!");
        } else {
            Console::print("Well, then... fine");
        }
    }

} // Alg