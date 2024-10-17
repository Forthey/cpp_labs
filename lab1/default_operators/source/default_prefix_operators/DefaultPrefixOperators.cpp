#include "DefaultPrefixOperators.hpp"

#include <cmath>

#include "DefaultPriorityRanges.hpp"


DefaultPrefixOperators::DefaultPrefixOperators() {
    opSymbolToInfo = {
            {"-", {DEFAULT_PREFIX_OPERATOR_PRIORITY, unaryMinus}}
    };
}


double DefaultPrefixOperators::unaryMinus(std::vector<double> const &numbers) {
    return -numbers[0];
}
