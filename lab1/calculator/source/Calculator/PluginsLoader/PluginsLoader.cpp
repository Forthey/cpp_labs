#include "PluginsLoader.hpp"

#include <windows.h>
#include <tchar.h>
#include <filesystem>
#include <iostream>

#include "export.hpp"


void PluginsLoader::loadPlugins() {
    loadedPlugins.clear();
    for (auto const &entry: std::filesystem::directory_iterator(dllDir)) {
        HMODULE dllHandler = LoadLibrary(_T(entry.path().string().c_str()));
        if (!dllHandler) {
            continue;
        }
        FARPROC getNameFuncAddr = GetProcAddress(dllHandler, "getName");
        FARPROC calcFuncAddr = GetProcAddress(dllHandler, "calc");
        FARPROC getTypeFuncAddr = GetProcAddress(dllHandler, "getType");
        FARPROC getPriorLevelFuncAddr = GetProcAddress(dllHandler, "getPriorityLevel");

        if (!calcFuncAddr || !getNameFuncAddr || !getTypeFuncAddr || !getPriorLevelFuncAddr)
            continue;

        std::function getNameFunc((decltype(&::getName)(getNameFuncAddr)));
        std::function calcFunc((decltype(&::calc)(calcFuncAddr)));
        std::function getTypeFunc((decltype(&::getType)(getTypeFuncAddr)));
        std::function getPriorityLevelFunc((decltype(&::getPriorityLevel)(getPriorLevelFuncAddr)));

        nameToFunc.emplace(
                getNameFunc(),
                CalcFuncWithInfo{
                getTypeFunc(),
                calcFunc,
                getPriorityLevelFunc()
        });
        loadedPlugins.emplace_back(dllHandler);
    }
}

bool PluginsLoader::contains(std::string const &opName, Tok::TokenType opType) {
    return nameToFunc.contains(opName) && nameToFunc.at(opName).type == opType;
}

std::function<double(std::vector<double> const &)> &PluginsLoader::getOpFunction(std::string const &opName) {
    return nameToFunc.at(opName).calcFunc;
}

uint8_t PluginsLoader::getPriorityLevel(std::string const &opName) {
    return nameToFunc.at(opName).priorityLevel;
}

void PluginsLoader::freePlugins() {
    loadedPlugins.clear();
}


PluginsLoader::DllWatcher::~DllWatcher() {
    FreeLibrary(dllHandler);
}
