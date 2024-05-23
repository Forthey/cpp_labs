#include <vector>
#include <string>
#include <iostream>

namespace Alg {
	template <typename Type>
	inline bool equalsToZero(Type number) {
		return std::abs(number) <= std::numeric_limits<Type>::epsilon();
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