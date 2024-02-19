#include <vector>
#include <string>
#include <iostream>

namespace Alg {
#define DEFAULT_EXP_DEGREE_MULTIPLIER 5
	template <typename Type>
	inline bool equalsToZero(Type number, int expDegMultiplier = DEFAULT_EXP_DEGREE_MULTIPLIER) {
		return std::abs(number) <= std::numeric_limits<Type>::epsilon() * exp(expDegMultiplier);
	}

	typedef std::vector<double> Roots;

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

}