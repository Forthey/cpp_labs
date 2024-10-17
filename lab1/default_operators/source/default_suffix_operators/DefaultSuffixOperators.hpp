#pragma once

#include "DefaultOperators.hpp"


class DefaultSuffixOperators : public DefaultOperators {
    static double addition(std::vector<double> const &numbers);

    static double subtraction(std::vector<double> const &numbers);

    static double multiplication(std::vector<double> const &numbers);

    static double division(std::vector<double> const &numbers);

    static double modulo(std::vector<double> const &numbers);
public:
    DefaultSuffixOperators();
};