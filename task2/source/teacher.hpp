#pragma once
#include "quadratic_equation.hpp"

class Teacher
{
	using Grades = std::vector<int>;

	class Student {
	public:
		std::string name, surname;
		Grades grades;
	};
public:
	void checkSolutions();
	void printGradesTable();
};

