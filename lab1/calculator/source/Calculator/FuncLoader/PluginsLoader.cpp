#include "PluginsLoader.hpp"

#include <windows.h>
#include <tchar.h>
#include <filesystem>
#include <iostream>


using getNameTemplate = std::string const &(*)();
using calcTemplate = double (*)(std::vector<double> const &);
using getTypeTemplate = Tok::TokenType (*)();
using getPriorityLevelTemplate = uint8_t (*)();


std::wstring const PluginsLoader::dllDir = L"plugins";
std::list<PluginsLoader::DllWatcher> PluginsLoader::loadedFunctions;
std::unordered_map<std::string, PluginsLoader::FuncWithInfo> PluginsLoader::nameToFunc;


void PluginsLoader::loadFunctions() {
    loadedFunctions.clear();
    for (auto const &entry: std::filesystem::directory_iterator(dllDir)) {
        HMODULE dllHandler = LoadLibrary(_T(entry.path().string().c_str()));
        if (!dllHandler)
            continue;
        FARPROC getNameFuncAddr = GetProcAddress(dllHandler, "getName");
        FARPROC calcFuncAddr = GetProcAddress(dllHandler, "calc");
        FARPROC getTypeFuncAddr = GetProcAddress(dllHandler, "getType");
        FARPROC getPriorLevelFuncAddr = GetProcAddress(dllHandler, "getPriorityLevel");

        if (!calcFuncAddr || !getNameFuncAddr || !getTypeFuncAddr)
            continue;
        nameToFunc.emplace(
                ((getNameTemplate) getNameFuncAddr)(),
                FuncWithInfo{
                        ((getTypeTemplate) getTypeFuncAddr)(),
                        (calcTemplate) calcFuncAddr,
                        ((getPriorityLevelTemplate)getPriorLevelFuncAddr)()
        });
        loadedFunctions.emplace_back(dllHandler);
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
    loadedFunctions.clear();
}


PluginsLoader::DllWatcher::~DllWatcher() {
    FreeLibrary(dllHandler);
}
