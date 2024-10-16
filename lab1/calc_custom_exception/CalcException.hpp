#pragma once

#include <iostream>
#include <format>


class CalcException : public std::exception {
    std::string const message;
public:
    explicit CalcException(std::string const &tag, std::string const &description) : message(
            std::format("{}: {}", tag, description)) {}

    char const *what() const noexcept override {
        return message.c_str();
    }
};
