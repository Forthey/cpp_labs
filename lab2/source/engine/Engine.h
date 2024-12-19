#pragma once
#include <functional>
#include <unordered_map>

#include "wrapper/Wrapper.h"


class Engine {
    using WrapperInvoker = std::function<std::any(ArgsDict)>;

    std::unordered_map<std::string, WrapperInvoker> commands;

    Engine();
public:
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    template<typename Class, typename ReturnType, typename... Args>
    Engine& registerCommand(const std::string &command, Wrapper<Class, ReturnType, Args...>* wrapper) {
        if (commands.contains(command)) {
            throw std::runtime_error(std::format("Command {} has been already registered", command));
        }

        commands.emplace(command, [wrapper](std::unordered_map<std::string, std::any> const &args) {
            if constexpr (std::is_void_v<ReturnType>) {
                (*wrapper)(args);
                return std::any(nullptr);
            } else {
                return std::any((*wrapper)(args));
            }

        });

        return *this;
    }

    template<typename ReturnType = void>
    ReturnType execute(std::string const& command, ArgsDict args) {
        if (!commands.contains(command)) {
            throw std::runtime_error(std::format("Command {} has not been registered before executing", command));
        }

        if constexpr (std::is_void_v<ReturnType>) {
            commands[command](args);
        } else {
            return std::any_cast<ReturnType>(commands[command](args));
        }
    }

    static Engine& inst();
};
