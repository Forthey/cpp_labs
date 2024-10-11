#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <queue>

#include "DefaultSuffixOperators.hpp"
#include "DefaultPrefixOperators.hpp"
#include "ComputableOperator.hpp"
#include "Operands.hpp"
#include "Parenthesis.hpp"


class TokenScanner {
    bool expectingOp;
    std::shared_ptr<std::queue<Tok::TokenPtr>> tokens;

    static double readNumber(std::string::const_iterator &iter, std::string const &expr);
    static std::string readName(std::string::const_iterator &iter, std::string const &expr);

    bool addOperator(char const ch) noexcept;

public:
    std::shared_ptr<std::queue<Tok::TokenPtr>> buildTokens(std::string const &expr);
};

