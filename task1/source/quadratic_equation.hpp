#include <vector>

namespace Alg {

	class QuadraticEq {
		double const a, b, c;
		std::vector<double> roots;
	public:
		QuadraticEq(double const a, double const b, double const c) : a(a), b(b), c(c) {};

		std::vector<double>& const solve();
		std::vector<double>& const getRoots();
	};

}