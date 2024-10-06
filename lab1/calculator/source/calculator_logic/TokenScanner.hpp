#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <queue>

#include "../tokens/suffix_operators/SuffixOperators.hpp"
#include "../tokens/operands/Operands.hpp"
#include "../tokens/Parenthesis.hpp"


class TokenScanner {
    static std::unordered_set<char> const availableOperators;

    static double readNumber(std::string::const_iterator &iter, std::string const &expr);

    static void addOperator(std::queue<TokenPtr> &tokens, char const ch) noexcept;

public:
    static std::shared_ptr<std::queue<TokenPtr>> buildTokens(std::string const &expr);
};

