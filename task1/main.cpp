#include <fstream>
#include "list.hpp"

int compareStrings(const std::string& s1, const std::string& s2) {
    return s1.compare(s2);
}

void test() {
    using namespace std;
    cout << "Тестовая программа считывает слова из words1.data и words2.data остортированно в списки, \nа затем записывает остортированный результирующий список в файл words12.data" << endl;
    cout << "Считывание списков в программу..." << endl;

    Alg::List<string> list1, list2;
    ifstream file1("files/words1.data"), file2("files/words2.data");

    if (!file1.is_open() || !file2.is_open()) {
        cout << "Не нашлись файлы *.data для теста, завершение..." << endl;
        return;
    }
    list1.readSorted(file1, compareStrings);
    list2.readSorted(file2, compareStrings);
    file1.close();
    file2.close();

    cout << "Списки считаны" << endl;
    cout << "Список 1 отсортирован?: " << (list1.sorted(compareStrings) ? "true" : "false") << endl;
    cout << "Список 2 отсортирован?: " << (list2.sorted(compareStrings) ? "true" : "false") << endl;

    Alg::List<std::string> list12 = (list1 + list2).sort(compareStrings);

    cout << "Результирующий список отсортирован?: " << (list12.sorted(compareStrings) ? "true" : "false") << endl;
    cout << "Записывание результирующего списка в файл..." << endl;

    ofstream file("files/words12.data");
    if (!file.is_open()) {
        cout << "Что - то помешало открыть файл words12.data, завершение..." << endl;
        return;
    }
    list12.display(file);
    file.close();
    cout << "Список записан" << endl;
}

void customFile() {
    using namespace std;
    string filename;

    cout << "Введите путь к первому файлу: ";
    cin >> filename;
    ifstream file1(filename);
    cout << "Введите путь ко второму файлу: ";
    cin >> filename;
    ifstream file2(filename);

    if (!file1.is_open() || !file2.is_open()) {
        cout << "Один из файлов не существует, выход..." << endl;
        return;
    }

    cout << "Считывание списков в программу..." << endl;
    Alg::List<string> list1, list2;
    list1.readSorted(file1, compareStrings);
    list2.readSorted(file2, compareStrings);
    file1.close();
    file2.close();

    cout << "Списки считаны" << endl;
    cout << "Список 1 отсортирован?: " << (list1.sorted(compareStrings) ? "true" : "false") << endl;
    cout << "Список 2 отсортирован?: " << (list2.sorted(compareStrings) ? "true" : "false") << endl;

    Alg::List<std::string> list12 = (list1 + list2).sort(compareStrings);

    cout << "Результирующий список отсортирован?: " << (list12.sorted(compareStrings) ? "true" : "false") << endl;

    cout << "display - вывести результирующий список" << endl;
    cout << "write - записать список в файл" << endl;
    cout << "back - выход" << endl;

    std::string response;
    cout << "> ";
    cin >> response;
    if (response == "display") {
        list12.display();
    }
    else if (response == "write") {
        cout << "Введите имя файла: ";
        cin >> filename;
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Что-то помешало открыть файл, завершение..." << endl;
            return;
        }

        cout << "Записывание результирующего списка в файл..." << endl;
        list12.display(file);
        file.close();
        cout << "Список записан" << endl;
    }
    else if (response == "back") {
        return;
    }
}

void customConsole() {
    using namespace std;
    Alg::List<string> list1, list2;
    size_t size;
    cout << "Создание первого списка" << endl;
    cout << "Введите число слов в списке: ";
    cin >> size;
    cout << "Введите " << size << " слов списка:" << endl;
    list1.readSorted(size, std::cin, compareStrings);

    cout << "Создание второго списка" << endl;
    cout << "Введите число слов в списке: ";
    cin >> size;
    cout << "Введите " << size << " слов списка : " << endl;
    list2.readSorted(size, std::cin, compareStrings);

    cout << "Списки считаны" << endl;
    cout << "Список 1 отсортирован?: " << (list1.sorted(compareStrings) ? "true" : "false") << endl;
    cout << "Список 2 отсортирован?: " << (list2.sorted(compareStrings) ? "true" : "false") << endl;

    Alg::List<std::string> list12 = (list1 + list2).sort(compareStrings);

    cout << "Результирующий список отсортирован?: " << (list12.sorted(compareStrings) ? "true" : "false") << endl;

    cout << "display - вывести результирующий список" << endl;
    cout << "write - записать список в файл" << endl;
    cout << "back - выход" << endl;

    std::string response;
    cout << "> ";
    cin >> response;
    if (response == "display") {
        list12.display();
    }
    else if (response == "write") {
        std::string filename;
        cout << "Введите имя файла: ";
        cin >> filename;
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Что-то помешало открыть файл, завершение..." << endl;
            return;
        }

        cout << "Записывание результирующего списка в файл..." << endl;
        list12.display(file);
        file.close();
        cout << "Список записан" << endl;
    }
    else if (response == "back") {
        return;
    }
}

void custom() {
    using namespace std;
    cout << "file - считывать файлов" << endl;
    cout << "console - считать из консоли" << endl;
    cout << "back - вернуться в основное меню" << endl;

    std::string response;
    cout << "> ";
    cin >> response;
    if (response == "file") {
        customFile();
    }
    else if (response == "console") {
        customConsole();
    }
    else if (response == "back") {
        return;
    }
    else {
        cout << "Неизвестная команда" << endl;
    }
}

void printMenuHelp() {
    using namespace std;
    cout << "test - Запустить тестовую программу" << endl;
    cout << "custom - Использовать собственные параметры" << endl;
    cout << "help - вывести это окно помощи" << endl;
    cout << "exit - Выйти" << endl;

}

void menu() {
    using namespace std;
    cout << "<< N1. Работа со списком (вариант 15) >>" << endl;
    printMenuHelp();

    bool isOpened = true;
    std::string response;
    while (isOpened) {
        cout << "> ";
        cin >> response;
        if (response == "test") {
            test();
        }
        else if (response == "custom") {
            custom();
        }
        else if (response == "help") {
            printMenuHelp();
        }
        else if (response == "exit") {
            isOpened = false;
        }
        else {
            cout << "Неизвестная команда (\"help\" - вывести список всех команд)" << endl;
        }
    }
}

int main() {
    system("chcp 1251");
    menu();
    return 0;
}