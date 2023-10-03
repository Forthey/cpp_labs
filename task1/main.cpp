#include "list.hpp"

int main() {
    List<int> list;

    for (int i = 0; i < 10; i++) {
        list.pushBack(i);
    }

    for (int i = 0; i < 10; i++) {
        bool popCheck;
        std::cout << list.popBack(popCheck) << " ";
    }
    return 0;
}