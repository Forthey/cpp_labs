#pragma once
#include <any>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include "utility/FunctionCallException.h"


template<std::size_t... Indices>
struct IndexSequence {
};

template<std::size_t N, std::size_t... Indices>
struct MakeIndexSequence : MakeIndexSequence<N - 1, N - 1, Indices...> {
};

template<std::size_t... Indices>
struct MakeIndexSequence<0, Indices...> : IndexSequence<Indices...> {
};


template<typename Class, typename Ret, typename... Args>
class Wrapper {
    Class *classInst;

    Ret (Class::*func)(Args...);

    std::vector<std::string> const argsList;

    std::vector<std::any> validateArgs(std::map<std::string, std::any> const &args) const;

    template <std::size_t... Indices>
    Ret call(IndexSequence<Indices...>, std::vector<std::any> const& argsValues) {
        return (classInst->*func)(std::any_cast<Args>(argsValues[Indices])...);
    }
public:
    using Method = Ret (Class::*)(Args...);

    Wrapper(Class *classInst, const Method f, std::vector<std::string> args)
        : classInst(classInst), func(f), argsList(std::move(args)) {
    }

    Ret operator()(std::map<std::string, std::any> const &args);

    void operator()(std::map<std::string, std::any> const &args, bool noReturn);
};


template<typename Class, typename Ret, typename... Args>
std::vector<std::any> Wrapper<Class, Ret, Args...>::validateArgs(std::map<std::string, std::any> const &args) const {
    std::vector<std::any> argsValues;

    if (args.size() != argsList.size()) {
        throw FunctionCallException(std::format("Wrong number of arguments: expected {}, found {}", argsList.size(),
                                                args.size()));
    }

    for (std::string const &arg : argsList) {
        if (!args.contains(arg)) {
            throw FunctionCallException(std::format("Argument not found: {}", arg));
        }
        argsValues.emplace_back(args.at(arg));
    }

    return argsValues;
}

template<typename Class, typename Ret, typename... Args>
Ret Wrapper<Class, Ret, Args...>::operator()(std::map<std::string, std::any> const &args) {
    auto argsValues = validateArgs(args);
    try {
        return call(MakeIndexSequence<sizeof...(Args)>{}, argsValues);
    } catch (std::exception const &e) {
        throw FunctionCallException(std::format("Wrong type of arguments ({})", e.what()));
    }
}

template<typename Class, typename Ret, typename... Args>
void Wrapper<Class, Ret, Args...>::operator()(std::map<std::string, std::any> const &args, bool noReturn) {
    auto argsValues = validateArgs(args);
    try {
        call(MakeIndexSequence<sizeof...(Args)>{}, argsValues);
    } catch (std::exception const &e) {
        throw FunctionCallException(std::format("Wrong type of arguments ({})", e.what()));
    }
}
