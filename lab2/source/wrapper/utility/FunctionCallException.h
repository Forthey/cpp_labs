#pragma once
#include <stdexcept>
#include <format>

class FunctionCallException : public std::exception {
      std::string message;
public:
    explicit FunctionCallException(std::string const& msg) : message(msg) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};
