#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>
#include <cstdint>


class DefaultOperators {
protected:
    class opInfo {
    public:
        std::uint8_t priorityLevel;
        std::function<double(std::vector<double> const &)> calcFunction;
    };

    std::unordered_map<std::string, opInfo> opSymbolToInfo;
public:
    bool contains(std::string const &opName);

    std::function<double(std::vector<double> const &)> getCalcFunction(std::string const &opName);

    std::uint8_t getPriorityLevel(std::string const &opName);
};
