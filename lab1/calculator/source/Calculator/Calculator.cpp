#include "Calculator.hpp"


double Calculator::calculate(std::string const& exprStr) {
    return polishCalculator.calculate(*converter.convert(*scanner.buildTokens(exprStr)));
}
