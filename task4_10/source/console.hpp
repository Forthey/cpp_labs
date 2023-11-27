#ifndef TASK4_10_CONSOLE_H
#define TASK4_10_CONSOLE_H
#include <iostream>

namespace Alg {

    class Console {
    public:
        static std::string request(const std::string &what);
        static void print(const std::string &what);
        static bool parseAnswer(const std::string &answer);
        static std::string readLine();
    };

} // Alg

#endif //TASK4_10_CONSOLE_H
