#include "notebook.hpp"

std::string generatePhoneNumber() {
    std::string phone = "+";

    const unsigned 
        countryCodeLength = rand() % 3 + 1, 
        operatorCodeLength = 3, 
        data1Length = 3, 
        data2Length = 2, 
        data3Length = 2;

    for (unsigned i = 0; i < countryCodeLength; i++) {
        phone += std::to_string(rand() % 9 + 1);
    }
    phone += "(";
    for (unsigned i = 0; i < operatorCodeLength; i++) {
        phone += std::to_string(rand() % 10);
    }
    phone += ")";
    for (unsigned i = 0; i < data1Length; i++) {
        phone += std::to_string(rand() % 10);
    }
    phone += "-";
    for (unsigned i = 0; i < data2Length; i++) {
        phone += std::to_string(rand() % 10);
    }
    phone += "-";
    for (unsigned i = 0; i < data3Length; i++) {
        phone += std::to_string(rand() % 10);
    }

    return phone;
}
void buildDatabase() {
    std::ifstream namesFile("data/fullnames.data");
    std::ofstream databaseFile("data/mammoths.note");

    if (!namesFile.is_open() || !databaseFile.is_open()) {
        std::cout << "Missed files, exiting..." << std::endl;
        return;
    }

    std::string surname, name;
    while (!namesFile.eof()) {
        namesFile >> name >> surname;
        databaseFile << surname << " " << generatePhoneNumber() << "\n";
    }
}

int main() {
    std::system("chcp 1251");
    std::locale::global(std::locale("ru_RU.utf8"));
    //buildDatabase();
    Alg::Notebook notebook;
    notebook.loadFromFile("data/mammoths.note");
    //notebook.display();
    return 0;
}