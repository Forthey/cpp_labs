#include "DefaultPrefixOperators.hpp"

#include <cmath>


DefaultPrefixOperators::DefaultPrefixOperators() {
    opSymbolToInfo = {
            {"-", {7, unaryMinus}}
    };
}


double DefaultPrefixOperators::unaryMinus(std::vector<double> const &numbers) {
    return -numbers[0];
}
