#pragma once
#include <unordered_map>
#include <cstdint>

class PriorityLevelStorage {
    static std::unordered_map<char, uint8_t> const priorityLevels;
public:
    [[nodiscard]] static uint8_t getLevelBySymbol(char const symbol) { return priorityLevels.at(symbol); }
};
