#pragma once

#include "DefaultOperators.hpp"


class DefaultPrefixOperators : public DefaultOperators {
    static double unaryMinus(std::vector<double> const &numbers);
public:
    DefaultPrefixOperators();
};