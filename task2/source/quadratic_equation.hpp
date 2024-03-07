#include <vector>
#include <string>
#include <iostream>


namespace Alg {
	using Roots = std::vector<double>;
	using QuadEqCoefs = std::array<double, 3>;


#define DEFAULT_EXP_DEGREE_MULTIPLIER 5
	template <typename Type>
	inline bool equalsToZero(Type number, int expDegMultiplier = DEFAULT_EXP_DEGREE_MULTIPLIER) {
		return std::abs(number) <= std::numeric_limits<Type>::epsilon() * exp(expDegMultiplier);
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
		std::string const inFilePath = "../data/input.txt";
		std::string const outFilePath = "../data/output.txt";

	public:
		bool buildEquations();
		std::vector<QuadEqCoefs> readEquations();
		bool writeSolution(std::string const& name, std::string const& surname, Roots const& roots);
		bool readNextSolution(QuadEqCoefs& quadEqCoefs, Roots& solution, std::string& stdntName, std::string& stdntSurname);
	};
}
