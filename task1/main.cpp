#include "list.hpp"
int main() {
    List<int> list;

    for (int i = 0; i < 10; i++) {
        list << i << i + 1;
    }

    list.display(std::cout);
    std::cout << list.find(5);
    std::cout << list.find(0);
    std::cout << list.find(10);
    return 0;
}