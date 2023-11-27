#include "console.hpp"

namespace Alg {
    void Console::print(const std::string &what) {
        std::cout << what << std::endl;
    }

    std::string Console::request(const std::string &what) {
        print(what);
        std::cout << "> ";
        std::string answer;
        answer = readLine();
        return answer;
    }

    bool Console::parseAnswer(const std::string &answer) {
        return answer == "Yes" || answer == "yes" || answer == "y" || answer == "Y";
    }

    std::string Console::readLine() {
        std::string response;
        std::getline(std::cin, response);
        return response;
    }

} // Alg