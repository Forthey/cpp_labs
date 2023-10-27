#include "notebook.hpp"

namespace Alg {

    Notebook::Notebook() {
        for (auto& list : persons) {
            list = std::make_unique<SelfOrganizingList<Person>>(comparefunc);
        }
    }

    int Notebook::index(const char letter)
    {
        if (enBegin < letter && letter < enEnd) {
            return letter - enBegin;
        }
        else if (enUpBegin < letter && letter < enUpEnd) {
            return letter - enUpBegin;
        }
        else if (ruBegin < letter && letter < ruEnd) {
            return letter - ruBegin + EN_LETTERS_COUNT;
        }
        else if (ruUpBegin < letter && letter < ruUpEnd) {
            return letter - ruUpBegin + EN_LETTERS_COUNT;
        }
        
        return 0;
    }

    char Notebook::toChar(const int index)
    {
        if (0 <= index && index < EN_LETTERS_COUNT)
            return index + enBegin;
        if (EN_LETTERS_COUNT <= index && index < PERSONS_SIZE)
            return index - EN_LETTERS_COUNT + ruBegin;
        return enBegin;
    }

    bool Notebook::loadFromFile(const std::string& fileName)
    {
        if (fileName.substr(fileName.find_last_of(".") + 1) != "note") {
            std::cout << "Wrong file format, exiting..." << std::endl;
            return false;
        }
        std::ifstream file(fileName);

        if (!file.is_open()) {
            std::cout << "Cannot open the file " << fileName << ", exiting..." << std::endl;
            return false;
        }
        std::string surname, phoneNumber;
        Person person;
        while (!file.eof()) {
            file >> surname >> phoneNumber;
            person = Person(surname, phoneNumber);
            persons[index(surname[0])]->push(person);
        }
        display();

        return true;
    }

    int Notebook::compareRule(const Person& mask, const Person& person) {
        if (person.surname.substr(0, mask.surname.length()) == mask.surname)
            return 0;
        return -1;
    }

    int Notebook::comparefunc(const Person& p1, const Person& p2) {
        return p1.surname.compare(p2.surname);
    }

    void Notebook::displayPerson(std::ostream& out, const Person& person) {
        out << person.surname << "\t" << person.phoneNumber;
    }

    Person Notebook::readPerson(std::istream& in) {
        Person person;
        in >> person.surname >> person.phoneNumber;
        return person;
    }

    void Notebook::display()
    {
        std::cout << "--- ENGLISH ---" << std::endl;
        for (unsigned char index = 0; index < persons.size(); index++) {
            if (index == EN_LETTERS_COUNT) {
                std::cout << "--- ÐÓÑÑÊÈÉ ---" << std::endl;
            }
            auto& list = *persons[index];
            std::string letter;
            letter += toChar(index);
            std::cout << letter << ":" << std::endl;
            //list.display(std::cout, displayPerson);
        }
    }

    void Notebook::test() {
        loadFromFile("test.data");
    }
}