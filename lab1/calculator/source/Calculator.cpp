#include "Calculator.hpp"

#include "calculator_logic/TokenScanner.hpp"
#include "calculator_logic/TokenConverter.hpp"
#include "calculator_logic/PolishCalculator.hpp"


double Calculator::calculate(std::string const& exprStr) {
    TokenConverter converter;

    return PolishCalculator::calculate(*converter.convert(*TokenScanner::buildTokens(exprStr)));
}