#pragma once

#include <queue>
#include <stack>
#include <memory>
#include <unordered_map>

#include "Operator.hpp"
#include "SuffixOperator.hpp"


class TokenConverter {
    enum ConvertState {
        WAITING_FOR_PREFIX = 0,
        WAITING_FOR_SUFFIX
    } state;

    std::shared_ptr<std::queue<Tok::TokenPtr>> resultTokens;
    std::unique_ptr<std::stack<Tok::OperatorPtr>> operatorsStack;

    static std::unordered_map<char, uint8_t> const opPriority;

    void dropOperators(Tok::OperatorPtr const &op);

    void parseForPrefix(Tok::TokenPtr &token);

    void parseForSuffix(Tok::TokenPtr &token);
public:
    std::shared_ptr<std::queue<Tok::TokenPtr>> convert(std::queue<Tok::TokenPtr> &tokens);
};
