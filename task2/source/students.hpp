#pragma once
#include <string>

#include "quadratic_equation.hpp"

class Student {
protected:
	std::string name, surname;
public:
	virtual void solveEquation() = 0;
};


class GoodStudent : Student {
public:
	void solveEquation() override;
};


class MidStudent : Student {
public:
	void solveEquation() override;
};


class BadStudent : Student {
public:
	void solveEquation() override;
};