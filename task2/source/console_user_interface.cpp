#include "console_user_interface.hpp"

#include <fstream>


std::unique_ptr<Teacher> ConsoleUserInterface::teacher;
std::unique_ptr<StudentsWorkSim> ConsoleUserInterface::studentsWorkSim;
ConsoleUserInterface::CommandRunner ConsoleUserInterface::commandRunner = {
	{"solve", solveEquations},
	{"generate", generateEquations},
	{"check", checkSolutions},
	{"grades", printGrades},
	{"exit", exitSim}
};


void ConsoleUserInterface::exitSim() {
	exit(0);
}


void ConsoleUserInterface::generateEquations() {
	std::cout << "Введите число уравнений (до 49 -- край разметки таблицы)" << std::endl;
	std::cout << "> ";

	int eqCnt;

	if (!(std::cin >> eqCnt)) {
		std::cout << "Неверный ввод..." << std::endl;
		return;
	}

	teacher->generateEquations(eqCnt);
}


void ConsoleUserInterface::printGrades() {
	teacher->printGradesTable();
}


void ConsoleUserInterface::solveEquations() {
	studentsWorkSim->simulateSolvings();
}


void ConsoleUserInterface::checkSolutions() {
	teacher->checkSolutions();
}


void ConsoleUserInterface::resetInOutFiles() {
	std::ofstream file(outputFileName);
	if (file.is_open()) {
		file.clear();
		file.close();
	}

	file.open(inputFileName);
	if (file.is_open()) {
		file.clear();
		file.close();
	}
}


void ConsoleUserInterface::printMenu() {
	std::cout << "solve - решить уравнения [Students]" << std::endl;
	std::cout << "generate - создать уравнения [Teacher]" << std::endl;
	std::cout << "check - проверить уравнения [Teacher]" << std::endl;
	std::cout << "grades - вывести таблицу успеваемости [Teacher]" << std::endl;
	std::cout << "exit - выйти" << std::endl;
	std::cout << "> ";
}


void ConsoleUserInterface::startSimulation() {
	std::string ans;

	while (true) {
		printMenu();
		std::cin >> ans;
		if (commandRunner.count(ans)) {
			commandRunner[ans]();
		}
		else {
			std::cout << "Команда не найдена" << std::endl;
		}
	}
}


void ConsoleUserInterface::startInteration() {
	std::setlocale(LC_ALL, "Russian");
	resetInOutFiles();

	std::cout << "--- Моделирование принятия зачета по математике ---" << std::endl;
	std::cout << "Введите начальные данные в формате:" << std::endl;
	std::cout << "<число студентов> (до 100, больше имён нету...) <доля хороших> < доля плохих>" << std::endl;
	std::cout << "> ";
	int studentsNum;
	double goodStudentProb, badStudentProb;

	if (!(std::cin >> studentsNum >> goodStudentProb >> badStudentProb)) {
		std::cout << "Похоже, введены неверные данные :(" << std::endl;
		return;
	}

	studentsWorkSim = std::make_unique<StudentsWorkSim>(studentsNum, goodStudentProb, badStudentProb);
	teacher = std::make_unique<Teacher>();

	startSimulation();
}
