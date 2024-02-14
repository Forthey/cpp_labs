#include <iostream>
#include <Windows.h>

#include "quadratic_equation.hpp"

class Program {
	enum Color {
		Blue = 1,
		GREEN,
		CYAN,
		RED,
		PURPLE,
		DARK_YELLOW,
		DEFAULT_WHITE,
		GRAY,
		BRIGHT_BLUE,
		BRIGTH_GREEN,
		BRIGHT_CYAN,
		BRIGHT_RED,
		PINK,
		YELLOW,
		BRIGHT_WHITE,
	};

    HANDLE hConsole;

	void print(std::string const& what, Color color = Color::DEFAULT_WHITE) {
		SetConsoleTextAttribute(hConsole, color);
		std::cout << what << std::endl;
		SetConsoleTextAttribute(hConsole, Color::DEFAULT_WHITE);
		std::cout << "> ";
	}

	void printProgramDescription() {
		std::cout << 
			"Made by Drekalov Nikita, group 5030102/20001" << std::endl <<
			"The program counts the roots of the quadratic equation" << std::endl <<
			"______________________________________________________" << std::endl;
	}
public:
	Program() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void start() {
		double a, b, c;

		printProgramDescription();

		while (true) {
			print("Input coefficients of quadratic equation ax^2+bx+c=0 separated by space\nType '0 0 0' to end program");
			if (!(std::cin >> a >> b >> c)) {
				print("ERROR: You should input 3 numbers separated by space to make program work", Color::RED);
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}

			if (a == 0 && b == 0 && c == 0) {
				break;
			}

			Alg::QuadraticEq equation(a, b, c);
			std::vector<double> const& roots = equation.solve();

			std::cout << "Equation " + equation.toString() + " has " << roots.size() << " real roots" << std::endl;
			for (double root : roots) { 
				std::cout << root << " ";
			}
			std::cout << std::endl << std::endl;

			std::cin.ignore(INT_MAX, '\n');
		}
	}
};

int main() {
	Program program;
	program.start();
	return 0;
}