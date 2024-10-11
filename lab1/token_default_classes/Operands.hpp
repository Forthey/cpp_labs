#pragma once

#include "Operand.hpp"


class Number : public Operand {
    double const value;
public:
    explicit Number(double const value) : value(value) {}

    [[nodiscard]] double getValue() const override { return value; }
};


class Variable : public Operand {
    std::string const name;
    std::shared_ptr<double> cachedValue;
public:
    explicit Variable(std::string const &name) : name(name) {}

    explicit Variable(std::string &&name) : name(name) {}

    [[nodiscard]] double getValue() const override { return *cachedValue; }
};
