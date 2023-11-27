#ifndef TASK4_10_CONSOLE_H
#define TASK4_10_CONSOLE_H
#include <iostream>

class Console {
public:
    static std::string request(const std::string &what);
    static void print(const std::string &what);
    static bool parseAnswer(const std::string &answer);
    static std::string readLine();
};

#endif //TASK4_10_CONSOLE_H
