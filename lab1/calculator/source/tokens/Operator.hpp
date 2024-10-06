#pragma once
#include "Token.hpp"
#include "priority_level/PriorityLevelStorage.hpp"


class Operator : public Token {
protected:
    char const symbol;

    explicit Operator(char const symbol) : symbol(symbol) {}
public:
    auto operator<=>(Operator const& op) const {
        return PriorityLevelStorage::getLevelBySymbol(symbol) <=> PriorityLevelStorage::getLevelBySymbol(op.symbol);
    }

    [[nodiscard]] char getSymbol() const { return symbol; }
};


using OperatorPtr = std::shared_ptr<Operator>;