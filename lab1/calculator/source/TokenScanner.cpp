#include <format>
#include "TokenScanner.hpp"

std::unordered_set<char> const TokenScanner::availableOperators = {
        '+', '-', '*', '/', '%', '^', '(', ')'
};

double TokenScanner::readNumber(std::string::const_iterator &iter, std::string const &expr) {
    double number = 0.0;

    while (iter != expr.end() && std::isdigit(*iter)) {
        number = number * 10.0 + *iter - '0';
        ++iter;
    }
    if (iter == expr.end() || *iter != '.')
        return number;

    ++iter;
    double denominator = 0.1;
    while (iter != expr.end() && std::isdigit(*iter)) {
        number += (*iter - '0') * denominator;
        denominator /= 10.0;
        ++iter;
    }

    return number;
}

std::shared_ptr<std::queue<std::shared_ptr<Token>>> TokenScanner::buildTokens(std::string const &expr) {
    tokens = std::make_shared<std::queue<std::shared_ptr<Token>>>();

    for (auto iter = expr.begin(); iter != expr.end();) {
        char const ch = *iter;

        if (ch == ' ' || ch == '\n') {
            ++iter;
            continue;
        }
        if (availableOperators.contains(ch)) {
            tokens->push(std::make_shared<OperatorToken>(ch));
            ++iter;
        }
        else if (std::isdigit(ch)) {
            tokens->push(std::make_shared<NumberToken>(readNumber(iter, expr)));
        }
        else {
            throw std::runtime_error(std::format("ParseError: Unknown literal \"{}\"", ch));
        }
    }

    return tokens;
}
