#pragma once
#include <stdexcept>
#include <format>

class FunctionCallException : public std::exception {
      std::string message;
public:
    template <typename... Args>
    explicit FunctionCallException(const std::string& msg, Args... args) {
        std::format(message, args...);
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};
