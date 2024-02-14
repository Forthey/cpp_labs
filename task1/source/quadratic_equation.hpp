#include <vector>
#include <string>

namespace Alg {

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