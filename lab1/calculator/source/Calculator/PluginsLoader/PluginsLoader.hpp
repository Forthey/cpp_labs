#pragma once

#include <windef.h>
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include "Token.hpp"


class PluginsLoader {
    class DllWatcher {
        HMODULE dllHandler;
    public:
        explicit DllWatcher(HMODULE dllHandler) : dllHandler(dllHandler) {}

        ~DllWatcher();
    };

    class FuncWithInfo {
    public:
        Tok::TokenType type;
        std::function<double(std::vector<double> const &)> calcFunc;
        uint8_t priorityLevel;
    };

    static std::wstring const dllDir;
    static std::list<DllWatcher> loadedFunctions;
    static std::unordered_map<std::string, FuncWithInfo> nameToFunc;
public:
    static void loadPlugins();

    static bool contains(std::string const &opName, Tok::TokenType opType);

    static std::function<double(std::vector<double> const &)> &getOpFunction(std::string const &opName);

    static uint8_t getPriorityLevel(std::string const &opName);

    static void freePlugins();
};
