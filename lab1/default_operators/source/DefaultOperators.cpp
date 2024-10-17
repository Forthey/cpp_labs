#include "DefaultOperators.hpp"

bool DefaultOperators::contains(std::string const &opName) {
    return opSymbolToInfo.contains(opName);
}

std::function<double(std::vector<double> const &)> DefaultOperators::getCalcFunction(std::string const &opName) {
    return opSymbolToInfo.at(opName).calcFunction;
}

std::uint8_t DefaultOperators::getPriorityLevel(std::string const &opName) {
    return opSymbolToInfo.at(opName).priorityLevel;
}
