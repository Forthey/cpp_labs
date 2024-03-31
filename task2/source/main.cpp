#include <fstream>

#include "students_work_sim.hpp"
#include "teacher.hpp"


void resetOutputFile() {
	std::ofstream file(outputFileName);

	file.clear();
	file.close();
}


void printMenu() {
	std::cout << "--- ћоделирование прин€ти€ зачета по математике ---" << std::endl;
	std::cout << "1. teacher - роль учител€" << std::endl;
	std::cout << "2. students - решить кр" << std::endl;
}


void startSimulation(int studentsNum, double goodStudentProb, double badStudentProb) {
	Teacher teacher;
	StudentsWorkSim studentsWorkSim(studentsNum, goodStudentProb, badStudentProb);
	teacher.generateEquations(49);
	studentsWorkSim.simulateSolvings();
	teacher.checkSolutions();
	teacher.printGradesTable();
}


int main() {
	std::setlocale(LC_ALL, "Russian");

	resetOutputFile();

	printMenu();
	std::cout << "¬ведите начальные данные в формате:" << std::endl;
	std::cout << "<число студентов> (до 100, больше имЄн нету...) <дол€ хороших> < дол€ плохих>" << std::endl;
	std::cout << "> ";
	int studentsNum;
	double goodStudentProb, badStudentProb;

	if (!(std::cin >> studentsNum >> goodStudentProb >> badStudentProb)) {
		std::cout << "ѕохоже, введены неверные данные :(" << std::endl;
		return 1;
	}

	startSimulation(studentsNum, goodStudentProb, badStudentProb);

	return 0;
}