#pragma once

#include <cmath>

#include "SuffixOperator.hpp"


class AdditionOperator : public SuffixOperator {
public:
    AdditionOperator() : SuffixOperator('+') {}

    double calculate(std::vector<double> const &numbers) final {
        return numbers[0] + numbers[1];
    }
};


class SubtractionOperator : public SuffixOperator {
public:
    SubtractionOperator() : SuffixOperator('-') {}

    double calculate(std::vector<double> const &numbers) final {
        return numbers[0] - numbers[1];
    }
};


class MultiplicationOperator : public SuffixOperator {
public:
    MultiplicationOperator() : SuffixOperator('*') {}

    double calculate(std::vector<double> const &numbers) final {
        return numbers[0] * numbers[1];
    }
};


class DivisionOperator : public SuffixOperator {
public:
    DivisionOperator() : SuffixOperator('/') {}

    double calculate(std::vector<double> const &numbers) final {
        return numbers[0] / numbers[1];
    }
};


class ModuloOperator : public SuffixOperator {
public:
    ModuloOperator() : SuffixOperator('%') {}

    double calculate(std::vector<double> const &numbers) final {
        return static_cast<int64_t>(numbers[0]) % static_cast<int64_t>(numbers[1]);
    }
};


class PowOperator : public SuffixOperator {
public:
    PowOperator() : SuffixOperator('^') {}

    double calculate(std::vector<double> const &numbers) final {
        return std::pow(numbers[0], numbers[1]);
    }
};