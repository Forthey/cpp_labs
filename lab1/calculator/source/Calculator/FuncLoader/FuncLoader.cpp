#include "FuncLoader.hpp"

#include <windows.h>
#include <tchar.h>
#include <filesystem>
#include <iostream>


using getNameTemplate = std::string const& (*)();
using calcTemplate = double (*)(std::vector<double> const&);

std::wstring const FuncLoader::dllDir = L"funcs";
std::list<FuncLoader::DllWatcher> FuncLoader::loadedFunctions;
std::unordered_map<std::string, std::function<double(std::vector<double> const &)>> FuncLoader::nameToFunc;


void FuncLoader::loadFunctions() {
    loadedFunctions.clear();
    for (auto const& entry : std::filesystem::directory_iterator(dllDir)) {
        HMODULE dllHandler = LoadLibrary(_T(entry.path().string().c_str()));
        if (!dllHandler)
            continue;
        FARPROC getNameFuncAddr = GetProcAddress(dllHandler, "getName");
        FARPROC calcFuncAddr = GetProcAddress(dllHandler, "calc");
        if (!calcFuncAddr || !getNameFuncAddr)
            continue;
        nameToFunc.emplace(((getNameTemplate)getNameFuncAddr)(), (calcTemplate)calcFuncAddr);
        loadedFunctions.emplace_back(dllHandler);
    }
}

bool FuncLoader::contains(std::string const& funcName) {
    return nameToFunc.contains(funcName);
}

std::function<double(std::vector<double> const &)>& FuncLoader::getFunction(std::string const& funcName) {
    return nameToFunc.at(funcName);
}

void FuncLoader::freeFuncs() {
    loadedFunctions.clear();
}


FuncLoader::DllWatcher::~DllWatcher() {
    FreeLibrary(dllHandler);
    std::cout << "cleared func" << std::endl;
}
