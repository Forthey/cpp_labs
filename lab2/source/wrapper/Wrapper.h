#pragma once
#include <any>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "utility/FunctionCallException.h"


using ArgsDict = std::unordered_map<std::string, std::any> const &;


template<std::size_t... Indices>
struct IndexSequence {
};

template<std::size_t N, std::size_t... Indices>
struct MakeIndexSequence : MakeIndexSequence<N - 1, N - 1, Indices...> {
};

template<std::size_t... Indices>
struct MakeIndexSequence<0, Indices...> : IndexSequence<Indices...> {
};


template<typename Class, typename ReturnType, typename... Args>
class Wrapper {
    Class* classInst;

    ReturnType (Class::*func)(Args...);

    std::vector<std::string> const argsList;

    std::vector<std::any> validateArgs(ArgsDict args) const;

    template<std::size_t... Indices>
    ReturnType call(IndexSequence<Indices...>, std::vector<std::any> const &argsValues) {
        return (classInst->*func)(std::any_cast<Args>(argsValues[Indices])...);
    }

public:
    using ClassMethod = ReturnType (Class::*)(Args...);

    Wrapper(Class *classInst, const ClassMethod f, std::vector<std::string> args)
        : classInst(classInst), func(f), argsList(std::move(args)) {
    }

    ReturnType operator()(ArgsDict args);

    void operator()(ArgsDict args, bool noReturn);
};


template<typename Class, typename ReturnType, typename... Args>
std::vector<std::any> Wrapper<Class, ReturnType, Args...>::validateArgs(ArgsDict args) const {
    std::vector<std::any> argsValues;

    if (args.size() != argsList.size()) {
        throw FunctionCallException(std::format(
            "Wrong number of arguments: expected {}, found {}", argsList.size(), args.size()
        ));
    }

    for (std::string const &arg: argsList) {
        if (!args.contains(arg)) {
            throw FunctionCallException(std::format("Argument not found: {}", arg));
        }
        argsValues.emplace_back(args.at(arg));
    }

    return argsValues;
}

template<typename Class, typename ReturnType, typename... Args>
ReturnType Wrapper<Class, ReturnType, Args...>::operator()(ArgsDict args) {
    auto argsValues = validateArgs(args);
    try {
        if constexpr (std::is_void_v<ReturnType>) {
            call(MakeIndexSequence<sizeof...(Args)>{}, argsValues);
        } else {
            return call(MakeIndexSequence<sizeof...(Args)>{}, argsValues);
        }
    } catch (std::exception const &e) {
        throw FunctionCallException(std::format("Wrong type of arguments ({})", e.what()));
    }
}
