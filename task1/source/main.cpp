#include <iostream>
#include <Windows.h>

#include "quadratic_equation.hpp"

class ConsoleUserInterface {
#define ESTIMATED_BAD_MAX_LIMIT 10000000.0 // 10^7
#define ESTIMATED_BAD_MIN_LIMIT 0.0000001  // 10^-7

	enum Color {
		BLUE = 1,
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

	void print(std::string const& what, bool awaitResponseSymbol = false, Color color = Color::DEFAULT_WHITE) const {
		SetConsoleTextAttribute(hConsole, WORD(color));
		std::cout << what << std::endl;
		SetConsoleTextAttribute(hConsole, WORD(Color::DEFAULT_WHITE));
		if (awaitResponseSymbol) {
			std::cout << "> ";
		}
	}

	void printProgramDescription() const {
		std::cout << 
			"Made by Drekalov Nikita, group 5030102/20001" << std::endl <<
			"The program counts the roots of the quadratic equation" << std::endl <<
			"______________________________________________________" << std::endl;
	}
public:
	ConsoleUserInterface() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void startUserInteraction() const {
		double a, b, c;

		printProgramDescription();

		while (true) {
			print("Input coefficients of quadratic equation ax^2+bx+c=0 separated by space");
			print("Type '0 0 0' to end program");

			if (!(std::cin >> a >> b >> c)) {
				print("ERROR: You should input 3 numbers separated by space to make program work", false, Color::RED);
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				continue;
			}

			if (a == 0.0 && b == 0.0 && c == 0.0) {
				break;
			}

			if (abs(a) >= ESTIMATED_BAD_MAX_LIMIT || abs(b) >= ESTIMATED_BAD_MAX_LIMIT || abs(c) >= ESTIMATED_BAD_MAX_LIMIT) {
				print("In order to avoid large computational errors try to input modulo smaller coefficients", false, Color::YELLOW);
			}
			else if (abs(a) <= ESTIMATED_BAD_MIN_LIMIT || abs(b) <= ESTIMATED_BAD_MIN_LIMIT || abs(c) <= ESTIMATED_BAD_MIN_LIMIT) {
				print("In order to avoid large computational errors try to input modulo bigger coefficients", false, Color::YELLOW);
			}

			Alg::QuadraticEq equation(a, b, c);
			std::vector<double> const& roots = equation.solve();

			print("Equation " + equation.toString() + " has " + std::to_string(roots.size()) + " real roots");
			for (double root : roots) { 
				print(std::to_string(root), false, Color::GREEN);
			}
			std::cout << std::endl << std::endl;

			std::cin.ignore(INT_MAX, '\n');
		}
	}
};

int main() {
	ConsoleUserInterface cuiInstance;
	cuiInstance.startUserInteraction();
	return 0;
}