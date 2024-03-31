#include "teacher.hpp"

#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>


void Teacher::generateEquations(int eqCnt)
{
	const double 
		maxA = 100.0, 
		maxB = 1000.0, 
		maxC = 1000.0;

	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> 
		distA(-maxA, maxA),
		distB(-maxB, maxB),
		distC(-maxC, maxC);

	std::ofstream equationsFile(inputFileName);

	if (!equationsFile.is_open()) {
		std::cout << std::format("Missing '{}', exiting...\n", inputFileName);
	}

	double a, b, c;
	for (int i = 0; i < eqCnt; i++) {
		a = distA(rd);
		b = distB(rd);
		c = distC(rd);

		equationsFile << QuadraticEq::toString(a, b, c) << std::endl;
	}

	equationsFile.close();
}


int numberLength(int number) {
	int length = 0;
	while (number != 0) {
		number /= 10;
		length++;
	}

	return length;
}


bool Teacher::checkRoot(Roots const& realRoots, double root)
{
	int rootLen = numberLength(int(root));
	bool rootFound = false;
	for (auto& realRoot : realRoots) {
		if (equals(realRoot, root, DEFAULT_PRECISION - rootLen)) {
			rootFound = true;
		}
	}
	return rootFound;
}


bool Teacher::checkRoots(std::ifstream& file, Roots const& realRoots)
{
	bool checkResult = true;
	double root;
	if (file >> root) {
		if (!checkRoot(realRoots, root)) {
			checkResult = false;
		}
	}
	else {
		file.clear();
		file.ignore(INT_MAX, '\n');

		if (realRoots.empty()) {
			return true;
		}
		return false;
	}
	if (file.peek() != '\n' && file >> root) {
		if (!checkRoot(realRoots, root)) {
			checkResult = false;
		}
	}
	return checkResult;
}


void Teacher::checkSolutions()
{
	std::ifstream solutionsFile(outputFileName);

	if (!solutionsFile.is_open()) {
		std::cout << std::format("Missing '{}', exiting...\n", outputFileName);
	}
	for (int i = 0; i < currentSolutionsBeginPos; i++) {
		solutionsFile.ignore(INT_MAX, '\n');
	}

	std::string surname;
	std::string eqStr;
	Roots realRoots;

	while (!solutionsFile.eof()) {
		std::getline(solutionsFile, eqStr);

		if (eqStr.empty()) {
			continue;
		}

		solutionsFile >> surname;

		realRoots = QuadraticEq(eqStr).solve();

		studentsGrades[surname].push_back(checkRoots(solutionsFile, realRoots));
	}

	solutionsFile.close();
}


void printHeader(int grandesNum, int blockWidth, int surnameWidth) {
	int length = surnameWidth + 1 + grandesNum * (blockWidth + 1);

	std::cout << std::setw(surnameWidth) << " " << "|";
	for (int i = 0; i < grandesNum; i++) {
		std::cout << std::format("{:^3}|", i + 1);
	}
	std::cout << std::endl;
	for (int i = 0; i < length; i++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}


void Teacher::printGradesTable()
{
	if (studentsGrades.empty()) {
		std::cout << "<No grades recorded>" << std::endl;
		return;
	}

	int const blockWidth = 3;
	int const surnameWidth = 12;
	bool isFirst = true;
	for (auto& [surname, grades] : studentsGrades) {
		if (isFirst) {
			printHeader(static_cast<int>(grades.size()), blockWidth, surnameWidth);
			isFirst = false;
		}

		int length = surnameWidth + 1 + (blockWidth + 1) * static_cast<int>(grades.size());

		std::cout << std::setw(surnameWidth) << surname << "|";

		for (int i = 0; i < grades.size(); i++) {
			std::cout << std::format("{:^3}|", grades[i] ? "+" : "-");
		}
		std::cout << std::endl;

		for (int i = 0; i < length; i++) {
			std::cout << "-";
		}
		std::cout << std::endl;
	}
}
