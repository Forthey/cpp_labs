#pragma once

#include <string>
#include <memory>
#include <unordered_set>
#include <queue>

#include "ComputableOperator.hpp"
#include "Operands.hpp"
#include "Parenthesis.hpp"

#include "DefaultSuffixOperators.hpp"
#include "DefaultPrefixOperators.hpp"
#include "DefaultPostfixOperators.hpp"

#include "PluginsLoader/PluginsLoader.hpp"


class TokenScanner {
    DefaultPrefixOperators defaultPrefixOperators;
    DefaultSuffixOperators defaultSuffixOperators;
    DefaultPostfixOperators defaultPostfixOperators;
    PluginsLoader pluginsLoader;

    bool expectingOp = false;
    std::shared_ptr<std::queue<Tok::TokenPtr>> tokens;

    static double readNumber(std::string::const_iterator &iter, std::string const &expr);

    bool loadFunction(DefaultOperators &defaultOperators,
                             std::function<double(std::vector<double> const &)> &func, std::uint8_t &priorityLevel,
                             Tok::TokenType const opType, std::string const &opName);

    static std::string readName(std::string::const_iterator &iter, std::string const &expr);

    bool addOperator(std::string const &opName) noexcept;

public:
    TokenScanner() { pluginsLoader.loadPlugins(); }

    std::shared_ptr<std::queue<Tok::TokenPtr>> buildTokens(std::string const &expr);
};
