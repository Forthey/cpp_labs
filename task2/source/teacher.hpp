#pragma once
#include <map>

#include "quadratic_equation.hpp"

class Teacher
{
	using Grades = std::vector<bool>;

	std::map<std::string const, Grades> studentsGrades;
	int currentSolutionsBeginPos = 0;

	bool checkRoot(Roots const& realRoots, double root);
	bool checkRoots(std::ifstream &file, Roots const& realRoots);
public:
	void generateEquations(int eqCnt);
	void checkSolutions();
	void printGradesTable();
};

