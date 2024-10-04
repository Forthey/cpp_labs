#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <queue>

#include "Tokens/Tokens.hpp"

class TokenScanner {
    static std::unordered_set<char> const availableOperators;
    std::shared_ptr<std::queue<std::shared_ptr<Token>>> tokens;

    static double readNumber(std::string::const_iterator &iter, std::string const &expr);
public:
    std::shared_ptr<std::queue<std::shared_ptr<Token>>> buildTokens(std::string const &expr);
};

