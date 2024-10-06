#pragma once

#include <queue>
#include <stack>
#include <memory>
#include <unordered_map>

#include "../tokens/Operator.hpp"
#include "../tokens/suffix_operators/SuffixOperator.hpp"


class TokenConverter {
    enum ConvertState {
        WAITING_FOR_PREFIX = 0,
        WAITING_FOR_SUFFIX
    } state;

    std::shared_ptr<std::queue<TokenPtr>> queue;
    std::unique_ptr<std::stack<OperatorPtr>> stack;

    static std::unordered_map<char, uint8_t> const opPriority;

    void dropOperators(OperatorPtr const &op);

    void parseForPrefix(TokenPtr &token);

    void parseForSuffix(TokenPtr &token);
public:
    std::shared_ptr<std::queue<TokenPtr>> convert(std::queue<TokenPtr> &tokens);
};
