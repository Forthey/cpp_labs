#include "TokenScanner.hpp"

#include <format>
#include <iostream>

#include "SuffixOperator.hpp"
#include "PrefixOperator.hpp"
#include "FuncLoader/FuncLoader.hpp"
#include "Function.hpp"


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

std::string TokenScanner::readName(std::string::const_iterator &iter, std::string const &expr) {
    std::string name;
    while (iter != expr.end() && std::isalpha(*iter)) {
        name += *iter;
        ++iter;
    }

    return name;
}

std::shared_ptr<std::queue<std::shared_ptr<Tok::Token>>> TokenScanner::buildTokens(std::string const &expr) {
    tokens = std::make_shared<std::queue<Tok::TokenPtr>>();
    expectingOp = false;

    for (auto iter = expr.begin(); iter != expr.end();) {
        char const ch = *iter;

        if (ch == ' ' || ch == '\n') {
            ++iter;
            continue;
        }
        if (addOperator(ch)) {
            ++iter;
        }
        else if (std::isdigit(ch)) {
            tokens->push(std::make_shared<Tok::Number>(readNumber(iter, expr)));
            expectingOp = true;
        } else if (std::isalpha(ch)) {
            std::string name = readName(iter, expr);

            if (FuncLoader::contains(name)) {
                tokens->emplace(std::make_shared<Tok::Function>(name, FuncLoader::getFunction(name)));
            } else {
                throw std::runtime_error(std::format("ScanError: Unknown name \"{}\"", name));
            }
        }
        else {
        }
    }

    return tokens;
}

bool TokenScanner::addOperator(char const ch) noexcept {
    if (ch == '(')
        tokens->emplace(std::make_shared<Tok::OpeningParenthesis>());
    else if (ch == ')')
        tokens->emplace(std::make_shared<Tok::ClosingParenthesis>());
    else if (DefaultSuffixOperators::contains(ch) && expectingOp) {
        tokens->emplace(std::make_shared<Tok::SuffixOperator>(
                std::string(1, ch),
                DefaultSuffixOperators::getPriorityLevel(ch),
                DefaultSuffixOperators::getCalcFunction(ch)
        ));
        expectingOp = false;
    }
    else if (DefaultPrefixOperators::contains(ch) && !expectingOp)
        tokens->emplace(std::make_shared<Tok::PrefixOperator>(
                std::string(1, ch),
                DefaultPrefixOperators::getPriorityLevel(ch),
                DefaultPrefixOperators::getCalcFunction(ch)
        ));
    else
        return false;
    return true;
}
