#pragma once
#include <format>
#include <vector>
#include <string>
#include <iostream>


using Roots = std::vector<double>;
using QuadEqCoefs = std::array<double, 3>;


std::string const inputFileName = "input.txt";
std::string const outputFileName = "output.txt";


constexpr int DEFAULT_DEGREE_MULTIPLIER = 2;
template <typename Type>
inline bool equalsToZero(Type number, int expDegMultiplier = DEFAULT_DEGREE_MULTIPLIER) {
	return std::abs(number) <= std::numeric_limits<Type>::epsilon() * (1 << DEFAULT_DEGREE_MULTIPLIER);
}

constexpr int DEFAULT_PRECISION = 15;
inline bool equals(double number1, double number2, int precision = DEFAULT_PRECISION) {
	return std::abs(number2 - number1) < std::pow(10.0, -precision);
}

class QuadraticEq {
	double a = 0, b = 0, c = 0;
	Roots roots;

	void solveAsLinear();
	void solveAsQuadratic();
public:
	QuadraticEq(double const a, double const b, double const c);
	QuadraticEq(std::string const& equationAsString);

	Roots const & solve();
	Roots const & getRoots() const;
	std::string const toString() const;
	static std::string const toString(double a, double b, double c);
};
