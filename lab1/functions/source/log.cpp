#include "export.hpp"

#include <cmath>
#include <stdexcept>

std::string const name = "log";

std::string const& getName() {
    return name;
}

double calc(std::vector<double> const &x) {
    if (x[0] < 0.0) {
        throw std::runtime_error("CalcError: log argument must be more than 0");
    }
    return static_cast<double>(std::log(static_cast<long double>(x[0])));
}
