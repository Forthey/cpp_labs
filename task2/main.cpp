#include <iomanip>
#include <fstream>
#include "list.hpp"

class Person {
public:
    std::string surname;
    std::string phoneNumber;
};

int rule(const Person& mask, const Person& person) {
    if (person.surname.substr(0, mask.surname.length()) == mask.surname)
        return 0;
    return -1;
}

int comparefunc(const Person& p1, const Person& p2) {
    return p1.surname.compare(p2.surname);
}

void displayPerson(std::ostream& out, const Person& person) {
    out << person.surname << "\t" << person.phoneNumber;
}

Person readPerson(std::istream& in) {
    Person person;
    in >> person.surname >> person.phoneNumber;
    return person;
}

void test() {
    using namespace std;
    Alg::SelfOrganizingList<Person> list(comparefunc);

    fstream file;
    file.open("test.data", std::ifstream::in);
    list.read(file, readPerson);
    file.close();

    list.display(cout, displayPerson);
    list.findAll(Person("ma", ""), rule).display(cout, displayPerson);

    file.open("test.data", std::ofstream::out);
    list.display(file, displayPerson);
    file.close();
}

int main() {
    std::locale::global(std::locale("ru_RU.utf8"));
    test();
    return 0;
}