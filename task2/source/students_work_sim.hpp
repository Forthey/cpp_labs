#pragma once
#include <memory>

#include "students.hpp"


class StudentsWorkSim
{
	std::vector<std::unique_ptr<Student>> students;

	void fillStudents(size_t studentsNum, double goodStudentProb, double badStudentProb);
	void clipProbValues(double& prob1, double& prob2);
public:
	StudentsWorkSim(size_t studentsNum, double goodStudentProb, double badStudentProb);

	void simulateSolvings();
};

