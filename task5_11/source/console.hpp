#ifndef TASK4_10_CONSOLE_H
#define TASK4_10_CONSOLE_H
#include <iostream>

class Console {
public:
    typedef enum {
        Exit = 0,
        Add,
        Delete,
        Display,
        Intersect,
        Load,
        Save,
        Help,
        Hz
    } Answer;

    static std::string request(const std::string &what);
    static void print(const std::string &what);
    static Answer parseAnswer(const std::string &answer);
    static std::string readLine();
};

#endif //TASK4_10_CONSOLE_H
