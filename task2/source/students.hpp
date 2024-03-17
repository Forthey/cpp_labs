#pragma once
#include <vector>
#include <string>

#include "quadratic_equation.hpp"

std::string const inputFileName = "input.txt";
std::string const outputFileName = "output.txt";

class Student {
protected:
	std::string surname;

	bool readEquations(std::vector<QuadraticEq> &equations);
	bool writeRoots(std::vector<Roots>& allRoots);
public:
	virtual void solveEquations() = 0;

	~Student() {
		std::cout << "Destroyed yaay";
	}
};


class GoodStudent : public Student {
public:
	void solveEquations() override;

	~GoodStudent() {
		std::cout << "Student was destroyed yaaay";
	}
};


class MidStudent : public Student {
	double const solveProb = 0.55;

public:
	void solveEquations() override;

	~MidStudent() {
		std::cout << "Student was destroyed yaaay";
	}
};


class BadStudent : public Student {
public:
	void solveEquations() override;

	~BadStudent() {
		std::cout << "Student was destroyed yaaay";
	}
};