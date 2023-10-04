#include "list.hpp"

int compare(int a, int b) {
    return a - b;
}

int main() {
    Alg::List<int> list;

    for (int i = 0; i < 10; i++) {
        list << rand() % 15 << rand() % 25;
    }
    list.display(std::cout);
    list[5] = -5;
    list.display(std::cout);
    list.sort().display();
    return 0;
}