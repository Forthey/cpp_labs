#include "export.hpp"

#include <cmath>
#include <stdexcept>

std::string const name = "sin";

std::string const& getName() {
    return name;
}

double calc(std::vector<double> const &x) {
    return static_cast<double>(std::sin(static_cast<long double>(x[0])));
}
