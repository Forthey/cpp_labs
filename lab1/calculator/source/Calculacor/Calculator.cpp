#include "Calculator.hpp"

#include "TokenScanner.hpp"
#include "TokenConverter.hpp"
#include "PolishCalculator.hpp"


double Calculator::calculate(std::string const& exprStr) {
    TokenConverter converter;
    TokenScanner scanner;

    return PolishCalculator::calculate(*converter.convert(*scanner.buildTokens(exprStr)));
}