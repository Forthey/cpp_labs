#pragma once
#include <vector>
#include <string>

#include "quadratic_equation.hpp"


class Student {
protected:
	std::string surname;
	static int surnamePosInFile;

	void readEquations(std::vector<QuadraticEq> &equations);
	void writeRoots(std::vector<QuadraticEq> &equations, std::vector<Roots>& allRoots) const;
public:
	Student();

	std::string const& getSurname() const;

	virtual void solveEquations() = 0;
};


class GoodStudent : public Student {
public:
	void solveEquations() override;
};


class MidStudent : public Student {
	double const solveProb = 0.55;

public:
	void solveEquations() override;
};


class BadStudent : public Student {
public:
	void solveEquations() override;
};