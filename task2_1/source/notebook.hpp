#pragma once
#include <array>
#include <memory>
#include <iomanip>
#include <fstream>

#include "list.hpp"

namespace Alg {
    #define EN_LETTERS_COUNT 26
    #define RU_LETTERS_COUNT 33
    #define PERSONS_SIZE (EN_LETTERS_COUNT + RU_LETTERS_COUNT)

    class Person {
    public:
        explicit Person() = default;
        Person(std::string& surname, std::string& phoneNumber) : surname(surname), phoneNumber(phoneNumber) {}
        std::string surname;
        std::string phoneNumber;
    };

    class Notebook {

        std::array<std::unique_ptr<SelfOrganizingList<Person>>, PERSONS_SIZE> persons;
        const int enBegin = 'a', enEnd = 'z', enUpBegin = 'A', enUpEnd = 'Z', ruBegin = -32, ruEnd = -1, ruUpBegin = -64, ruUpEnd = -33;

        int index(const char letter);
        char toChar(const int index);
    public:
        explicit Notebook();

        bool loadFromFile(const std::string &fileName);
        static int compareRule(const Person& mask, const Person& person);
        static int comparefunc(const Person& p1, const Person& p2);
        static void displayPerson(std::ostream& out, const Person& person);
        static Person readPerson(std::istream& in);

        void display();
        void test();
    };

}



