#pragma once

#include <queue>
#include <stack>
#include <memory>
#include <unordered_map>

#include "Tokens/Tokens.hpp"


class TokenConverter {
    enum ConvertState {
        WAITING_FOR_PREFIX = 0,
        WAITING_FOR_SUFFIX
    } state;

    std::shared_ptr<std::queue<std::shared_ptr<Token>>> queue;
    std::unique_ptr<std::stack<std::shared_ptr<OperatorToken>>> stack;

    static std::unordered_map<char, uint8_t> const opPriority;
    void dropOperators(char const op);
    void parseForPrefix(std::shared_ptr<Token>& token);
    void parseForSuffix(std::shared_ptr<Token>& token);
public:
    std::shared_ptr<std::queue<std::shared_ptr<Token>>> convert(std::queue<std::shared_ptr<Token>>& tokens);
};
