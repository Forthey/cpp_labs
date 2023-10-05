#include <fstream>

#include "list.hpp"

int compareStrings(const std::string& s1, const std::string& s2) {
    return s1.compare(s2);
}

void test() {
    Alg::List<std::string> list1, list2;

    std::ifstream file1, file2;
    file1.open("files/words1.data");
    file2.open("files/words2.data");


    if (!file1.is_open() || !file2.is_open()) {
        std::cout << "Cannot find data files for test, exiting..." << std::endl;
        return;
    }

    list1.readSorted(1337, file1, compareStrings);
    list2.readSorted(1000, file2, compareStrings);

    std::cout << list1.sorted(compareStrings) << std::endl;
    std::cout << list2.sorted(compareStrings) << std::endl;

    Alg::List<std::string> allWords = (list1 + list2).sort(compareStrings);

    std::cout << allWords.sorted(compareStrings) << std::endl;
}

void menu() {
    using namespace std;
    cout << "<< 1. Работа со списком ";
}

int main() {
    std::locale::global(std::locale("ru_RU.utf8"));
    test();
    return 0;
}