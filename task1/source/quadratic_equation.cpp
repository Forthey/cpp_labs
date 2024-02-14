#include "quadratic_equation.hpp"

using namespace Alg;

QuadraticEq::QuadraticEq(double const a, double const b, double const c) : a(a), b(b), c(c) 
{
};

void QuadraticEq::solveAsLinear()
{
	if (b != 0) {
		roots.push_back(-c / b);
	}
}

void Alg::QuadraticEq::solveAsQuadratic()
{
	double D = b * b - 4 * a * c;

	if (D > 0) {
		roots.push_back((-b - sqrt(D)) / 2 / a);
		roots.push_back((-b + sqrt(D)) / 2 / a);
	}
	else if (D == 0) {
		roots.push_back(-b / 2 / a);
	}
}

std::vector<double> const & QuadraticEq::solve()
{
	if (a == 0) {
		solveAsLinear();
	}
	else {
		solveAsQuadratic();
	}

	return roots;
}

std::vector<double> const & QuadraticEq::getRoots() const
{
	return roots;
}

std::string const QuadraticEq::toString() const
{
	return std::to_string(a) + "*x^2 + " + std::to_string(b) + "*x + " + std::to_string(c) + " = 0";
}
