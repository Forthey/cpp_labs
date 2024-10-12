#pragma once

#include "DefaultOperators.hpp"


class DefaultPostfixOperators : public DefaultOperators {
protected:
    static double factorial(std::vector<double> const &numbers);
public:
    DefaultPostfixOperators();
};