#include "TokenScanner.hpp"

#include <format>
#include <iostream>

#include "SuffixOperator.hpp"
#include "PrefixOperator.hpp"
#include "PostfixOperator.hpp"
#include "DefaultSuffixOperators.hpp"
#include "DefaultPrefixOperators.hpp"
#include "DefaultPostfixOperators.hpp"
#include "FuncLoader/PluginsLoader.hpp"
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
        } else if (std::isdigit(ch)) {
            tokens->push(std::make_shared<Tok::Number>(readNumber(iter, expr)));
            expectingOp = true;
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

//template<class DefaultOperators>
//bool TokenScanner::loadFunction(std::function<double(std::vector<double> const &)>& func, std::uint8_t &priorityLevel,
//                                Tok::TokenType const opType, char const ch) {
//    auto chStr = std::string(1, ch);
//    if (DefaultOperators::contains(ch)) {
//        func = &DefaultOperators::getCalcFunction(ch);
//        priorityLevel = DefaultOperators::getPriorityLevel(ch);
//    } else if (PluginsLoader::contains(chStr, opType)) {
//        func = &PluginsLoader::getOpFunction(chStr);
//        priorityLevel = PluginsLoader::getPriorityLevel(chStr);
//    } else
//        return false;
//    return true;
//}

bool TokenScanner::addOperator(char const ch) noexcept {
//    std::function<double(std::vector<double> const &)> const* func;
//    std::uint8_t priorityLevel;
//    auto chStr = std::string(1, ch);
//
//    if (ch == '(')
//        tokens->emplace(std::make_shared<Tok::OpeningParenthesis>());
//    else if (ch == ')')
//        tokens->emplace(std::make_shared<Tok::ClosingParenthesis>());
//    else if (expectingOp && loadFunction<DefaultPostfixOperators>(func, priorityLevel, Tok::POSTFIX_OPERATOR, ch)) {
//        tokens->emplace(std::make_shared<Tok::PostfixOperator>(chStr, priorityLevel, *func));
//        expectingOp = false;
//    } else if (expectingOp && loadFunction<DefaultSuffixOperators>(func, priorityLevel, Tok::SUFFIX_OPERATOR, ch)) {
//        tokens->emplace(std::make_shared<Tok::SuffixOperator>(chStr, priorityLevel, *func));
//    } else if (!expectingOp && loadFunction<DefaultPrefixOperators>(func, priorityLevel, Tok::PREFIX_OPERATOR, ch)) {
//        tokens->emplace(std::make_shared<Tok::PrefixOperator>(chStr, priorityLevel, *func));
//    } else
//        return false;
//    return true;
    auto chStr = std::string(1, ch);
    if (ch == '(')
        tokens->emplace(std::make_shared<Tok::OpeningParenthesis>());
    else if (ch == ')')
        tokens->emplace(std::make_shared<Tok::ClosingParenthesis>());
    else if (expectingOp &&
             (DefaultPostfixOperators::contains(ch) || PluginsLoader::contains(chStr, Tok::POSTFIX_OPERATOR))) {
        std::function<double(std::vector<double> const &)> const *func;
        std::uint8_t priorityLevel;
        if (DefaultPostfixOperators::contains(ch)) {
            func = &DefaultPostfixOperators::getCalcFunction(ch);
            priorityLevel = DefaultPostfixOperators::getPriorityLevel(ch);
        } else if (PluginsLoader::contains(chStr, Tok::POSTFIX_OPERATOR)) {
            func = &PluginsLoader::getOpFunction(chStr);
            priorityLevel = PluginsLoader::getPriorityLevel(chStr);
        }

        tokens->emplace(std::make_shared<Tok::PostfixOperator>(chStr, priorityLevel, *func));
        expectingOp = false;
    } else if (expectingOp &&
             (DefaultSuffixOperators::contains(ch) || PluginsLoader::contains(chStr, Tok::SUFFIX_OPERATOR))) {
        std::function<double(std::vector<double> const &)> const *func;
        std::uint8_t priorityLevel;
        if (DefaultSuffixOperators::contains(ch)) {
            func = &DefaultSuffixOperators::getCalcFunction(ch);
            priorityLevel = DefaultSuffixOperators::getPriorityLevel(ch);
        } else if (PluginsLoader::contains(chStr, Tok::SUFFIX_OPERATOR)) {
            func = &PluginsLoader::getOpFunction(chStr);
            priorityLevel = PluginsLoader::getPriorityLevel(chStr);
        }

        tokens->emplace(std::make_shared<Tok::SuffixOperator>(chStr, priorityLevel, *func));
        expectingOp = false;
    } else if (!expectingOp &&
               (DefaultPrefixOperators::contains(ch) || PluginsLoader::contains(chStr, Tok::SUFFIX_OPERATOR))) {
        std::function<double(std::vector<double> const &)> const *func;
        std::uint8_t priorityLevel;
        if (DefaultPrefixOperators::contains(ch)) {
            func = &DefaultPrefixOperators::getCalcFunction(ch);
            priorityLevel = DefaultPrefixOperators::getPriorityLevel(ch);
        } else if (PluginsLoader::contains(chStr, Tok::PREFIX_OPERATOR)) {
            func = &PluginsLoader::getOpFunction(chStr);
            priorityLevel = PluginsLoader::getPriorityLevel(chStr);
        }

        tokens->emplace(std::make_shared<Tok::PrefixOperator>(chStr, priorityLevel, *func));
    } else
        return false;
    return true;
}
