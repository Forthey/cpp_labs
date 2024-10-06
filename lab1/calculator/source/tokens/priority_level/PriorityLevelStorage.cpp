#include "PriorityLevelStorage.hpp"

std::unordered_map<char, uint8_t> const PriorityLevelStorage::priorityLevels = {
        {'+', 4},
        {'-', 4},
        {'*', 5},
        {'/', 5},
        {'%', 5},
        {'^', 6},
        {'(', 0},
        {')', 1},
};