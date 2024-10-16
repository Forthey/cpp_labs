#pragma once

#include <windef.h>
#include <unordered_map>
#include <string>
#include <functional>
#include <utility>
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

    class CalcFuncWithInfo {
    public:
        Tok::TokenType type;
        std::function<double(std::vector<double> const &)> calcFunc;
        uint8_t priorityLevel;
    };

    std::wstring const dllDir;
    std::list<DllWatcher> loadedPlugins;
    std::unordered_map<std::string, CalcFuncWithInfo> nameToFunc;
public:
    PluginsLoader(std::wstring dllDir = L"plugins") : dllDir(std::move(dllDir)) {}

    ~PluginsLoader() { freePlugins(); }

    void loadPlugins();

    bool contains(std::string const &opName, Tok::TokenType opType);

    std::function<double(std::vector<double> const &)> &getOpFunction(std::string const &opName);

    uint8_t getPriorityLevel(std::string const &opName);

    void freePlugins();
};
