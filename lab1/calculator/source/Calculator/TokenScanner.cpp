#include "TokenScanner.hpp"

#include <format>
#include <iostream>

#include "SuffixOperator.hpp"
#include "PrefixOperator.hpp"
#include "PostfixOperator.hpp"
#include "PluginsLoader/PluginsLoader.hpp"
#include "Function.hpp"


TokenScanner::TokenScanner() {
    PluginsLoader::loadPlugins();
}


TokenScanner::~TokenScanner() {
    PluginsLoader::freePlugins();
}


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
        if (std::isdigit(ch)) {
            tokens->push(std::make_shared<Tok::Number>(readNumber(iter, expr)));
            expectingOp = true;
        } else if (addOperator(std::string(1, ch))) {
            ++iter;
        } else if (std::isalpha(ch)) {
            std::string name = readName(iter, expr);

            if (PluginsLoader::contains(name, Tok::PREFIX_OPERATOR)) {
                tokens->emplace(std::make_shared<Tok::Function>(name, PluginsLoader::getOpFunction(name)));
            } else {
                throw std::runtime_error(std::format("ScanError: Unknown name \"{}\"", name));
            }
        } else {
            throw std::runtime_error(std::format("ScanError: Unknown literal {}", ch));
        }
    }

    return tokens;
}


bool TokenScanner::loadFunction(DefaultOperators &defaultOperators,
                                std::function<double(std::vector<double> const &)> &func, std::uint8_t &priorityLevel,
                                Tok::TokenType const opType, std::string const &opName) {
    if (defaultOperators.contains(opName)) {
        func = defaultOperators.getCalcFunction(opName);
        priorityLevel = defaultOperators.getPriorityLevel(opName);
    } else if (PluginsLoader::contains(opName, opType)) {
        func = PluginsLoader::getOpFunction(opName);
        priorityLevel = PluginsLoader::getPriorityLevel(opName);
    } else
        return false;
    return true;
}


bool TokenScanner::addOperator(std::string const &opName) noexcept {
    std::function<double(std::vector<double> const &)> func;
    std::uint8_t priorityLevel;
    if (opName == "(")
        tokens->emplace(std::make_shared<Tok::OpeningParenthesis>());
    else if (opName == ")")
        tokens->emplace(std::make_shared<Tok::ClosingParenthesis>());
    else if (expectingOp &&
             loadFunction(defaultPostfixOperators, func, priorityLevel, Tok::POSTFIX_OPERATOR, opName)) {
        tokens->emplace(std::make_shared<Tok::PostfixOperator>(opName, priorityLevel, func));
    } else if (expectingOp &&
               loadFunction(defaultSuffixOperators, func, priorityLevel, Tok::SUFFIX_OPERATOR, opName)) {
        tokens->emplace(std::make_shared<Tok::SuffixOperator>(opName, priorityLevel, func));
        expectingOp = false;
    } else if (!expectingOp &&
               loadFunction(defaultPrefixOperators, func, priorityLevel, Tok::PREFIX_OPERATOR, opName)) {
        tokens->emplace(std::make_shared<Tok::PrefixOperator>(opName, priorityLevel, func));
    } else
        return false;
    return true;
}
