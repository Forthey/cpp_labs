#pragma once

#include <windef.h>
#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <list>


class FuncLoader {
    class DllWatcher {
        HMODULE dllHandler;
    public:
        explicit DllWatcher(HMODULE dllHandler) : dllHandler(dllHandler) {}
        ~DllWatcher();
    };

    static std::wstring const dllDir;
    static std::list<DllWatcher> loadedFunctions;
    static std::unordered_map<std::string, std::function<double(std::vector<double> const &)>> nameToFunc;
public:
    static void loadFunctions();

    static bool contains(std::string const &funcName);

    static std::function<double(std::vector<double> const &)> &getFunction(std::string const &funcName);

    static void freeFuncs();
};
