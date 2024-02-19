#include <vector>
#include <string>
#include <iostream>

namespace Alg {
#define DEFAULT_EXP_DEGREE_MULTIPLIER 5
	template <typename Type>
	inline bool equalsToZero(Type number, int expDegMultiplier = DEFAULT_EXP_DEGREE_MULTIPLIER) {
		return std::abs(number) <= std::numeric_limits<Type>::epsilon() * exp(expDegMultiplier);
	}

	class QuadraticEq {
		double const a, b, c;
		std::vector<double> roots;

		void solveAsLinear();
		void solveAsQuadratic();
	public:
		QuadraticEq(double const a, double const b, double const c);

		std::vector<double> const & solve();
		std::vector<double> const & getRoots() const;
		std::string const toString() const;
	};

}