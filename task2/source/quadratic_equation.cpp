#include "quadratic_equation.hpp"


std::string const QuadEquationIO::inFilePath = "../data/input.txt";
std::string const QuadEquationIO::outFilePath = "../data/output.txt";


QuadraticEq::QuadraticEq(double const a, double const b, double const c) : a(a), b(b), c(c) 
{
};

void QuadraticEq::solveAsLinear()
{
	if (!equalsToZero(b)) {
		roots.push_back(-c / b);
	}
}

void QuadraticEq::solveAsQuadratic()
{
	double D = b * b - 4.0 * a * c;

	if (D > 0.0) {
		roots.push_back((-b - sqrt(D)) / (2.0 * a));
		roots.push_back((-b + sqrt(D)) / (2.0 * a));
	}
	else if (equalsToZero(D)) {
		roots.push_back(-b / (2.0 * a));
	}
}

std::vector<double> const & QuadraticEq::solve()
{
	if (equalsToZero(a)) {
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
	return std::format("{}x^2 + {}x + {}", a, b, c);
}


