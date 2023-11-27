#include <fstream>
#include "expert.hpp"

namespace Alg {
    Expert::Expert(const std::string &path) {
        root = nullptr;

        if (!path.empty()) {
            load(path);
        }
    }

    void Expert::readRec(std::ifstream &file, QuestionTree **iter) {
        std::string what;
        std::getline(file, what);
        if (what == std::string(1, char(1))) {
            return;
        }
        *iter = new QuestionTree(what, nullptr, nullptr);
        readRec(file, &(*iter)->yes);
        readRec(file, &(*iter)->no);
    }

    bool Expert::load(const std::string &path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            Console::print("File doesn't exist");
            return false;
        }
        readRec(file, &root);
        file.close();
        return true;
    }

    void Expert::saveRec(std::ofstream &file, QuestionTree *iter) {
        if (iter == nullptr) {
            file << char(1) << std::endl;
            return;
        }
        file << iter->what << std::endl;
        saveRec(file, iter->yes);
        saveRec(file, iter->no);
    }

    bool Expert::save(const std::string &path) {
        std::ofstream file(path);
        if (!file.is_open()) {
            Console::print("Incorrect filename");
            return false;
        }
        saveRec(file, root);
        file.close();
        return true;
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
            if (Console::parseAnswer(Console::request(current->what + "?")) == Console::Yes) {
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
                if (current->yes == nullptr) {
                    readNewFeatureAndAnswer(current);
                } else {
                    readNewAnswer(current);
                }
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
        if (Console::parseAnswer(answer) == Console::Yes) {
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
        if (Console::parseAnswer(answer) == Console::Yes) {
            std::string name, feature;
            name = Console::request("Enter the object name");
            feature = Console::request("Describe the main feature of the " + name + " (Ex. \"Can swim\")");
            parent->addNo(feature, name);
            Console::print("Thanks! Now I'm ever smarter!");
        } else {
            Console::print("Well, then... fine");
        }
    }

    void Expert::readNewAnswer(Alg::QuestionTree *parent) {
        Console::print("Sorry, looks like I don't know what is it...");
        std::string answer = Console::request("Would you like to teach me a little?");
        if (Console::parseAnswer(answer) == Console::Yes) {
            std::string name;
            name = Console::request("Enter the object name which you've guessed");
            parent->addNo(name);
            Console::print("Thanks! Now I'm ever smarter!");
        } else {
            Console::print("Well, then... fine");
        }
    }


    void Expert::clear() {
        if (root != nullptr) {
            root->clear();
        }
        delete root;
    }

    Expert::~Expert() {
        clear();
    }

} // Alg