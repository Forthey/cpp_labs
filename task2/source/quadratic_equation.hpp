#pragma once
#include <format>
#include <vector>
#include <string>
#include <iostream>


using Roots = std::vector<double>;
using QuadEqCoefs = std::array<double, 3>;


constexpr int DEFAULT_DEGREE_MULTIPLIER = 2;

template <typename Type>
inline bool equalsToZero(Type number, int expDegMultiplier = DEFAULT_DEGREE_MULTIPLIER) {
	return std::abs(number) <= std::numeric_limits<Type>::epsilon() * (1 << DEFAULT_DEGREE_MULTIPLIER);
}


class QuadraticEq {
	double const a, b, c;
	Roots roots;

	void solveAsLinear();
	void solveAsQuadratic();
public:
	QuadraticEq(double const a, double const b, double const c);

	Roots const & solve();
	Roots const & getRoots() const;
	std::string const toString() const;
};


class QuadEquationIO {
	static std::string const inFilePath;
	static std::string const outFilePath;

public:
	static std::string const quadEqToString(double const a, double const b, double const c);
	static QuadEqCoefs const quadEqFromString(std::string const& equationAsStr);

	static bool buildEquations();
	static std::vector<QuadEqCoefs> readEquations();

	static bool writeSolution(std::string const& name, std::string const& surname, Roots const& roots);
	static bool readNextSolution(QuadEqCoefs& quadEqCoefs, Roots& solution, std::string& stdntName, std::string& stdntSurname);
};
