#pragma once
#include <any>
#include <map>
#include <set>
#include <string>

#include "utility/Value.h"
#include "utility/FunctionCallException.h"


template <typename Ret, typename... Args>
class Wrapper {
    Ret (*func)(Args...);
    std::set<std::string> const argsList;
public:
    explicit Wrapper(Ret (*f)(Args...), std::set<std::string> args) : func(f), argsList(std::move(args)) {}

    Ret operator()(std::map<std::string, std::any> const& args);
};

template<typename Ret, typename ... Args>
Ret Wrapper<Ret, Args...>::operator()(std::map<std::string, std::any> const &args) {
    std::set<std::any> argsValues;

    if (args.size() != argsList.size()) {
        throw FunctionCallException("Wrong number of arguments: expected {}, found {}", argsList.size(), args.size());
    }

    for (auto const& arg : argsList) {
        if (!args.contains(arg)) {
            throw FunctionCallException("Argument not found: {}", arg);
        }
    }

    try {
        Ret returnValue = std::apply(func, argsValues);

        return returnValue;
    } catch (std::exception const& e) {
        throw FunctionCallException("Wrong type of arguments ({})", e.what());
    }
}
