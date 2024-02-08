#include "quadratic_equation.hpp"

std::vector<double>& const Alg::QuadraticEq::solve()
{
	double D = b * b - 4 * a * c;

	if (D > 0) {
		roots.push_back((-b - sqrt(D)) / 2 / a);
		roots.push_back((-b + sqrt(D)) / 2 / a);
	}
	else if (D == 0) {
		roots.push_back(-b / 2 / a);
	}

	return roots;
}

std::vector<double>& const Alg::QuadraticEq::getRoots()
{
	return roots;
}
