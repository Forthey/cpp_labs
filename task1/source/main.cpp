#include <iostream>
#include <string>
#include "quadratic_equation.hpp"

class Program {
public:
	void print(std::string const& what) {
		std::cout << what << std::endl;
		std::cout << "> ";
	}

	void start() {
		while (true) {
			print("Input coefficients of quadratic equation ax^2+bx+c=0 separated by space\nType '0 0 0' to end program");
			double a, b, c;
			std::cin >> a >> b >> c;

			if (a == 0 && b == 0 && c == 0) {
				break;
			}

			Alg::QuadraticEq equation(a, b, c);
			std::vector<double> const& roots = equation.solve();

			std::cout << "Equation has " << roots.size() << " real roots: ";
			for (double root : roots) { 
				std::cout << root << " ";
			}
			std::cout << std::endl;
		}
	}
};

int main() {
	Program program;
	program.start();
	return 0;
}