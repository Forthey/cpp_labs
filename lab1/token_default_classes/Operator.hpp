#pragma once

#include <string>
#include <cstdint>

#include "Token.hpp"


namespace Tok {

    class Operator : public Token {
    protected:
        std::string const name;
        std::uint8_t priorityLevel;

        explicit Operator(std::string const &name, std::uint8_t const priorityLevel)
                : name(name), priorityLevel(priorityLevel) {}

    public:
        auto operator<=>(Operator const &op) const {
            return priorityLevel <=> op.priorityLevel;
        }

        [[nodiscard]] std::string const &getName() const { return name; }
    };


    using OperatorPtr = std::shared_ptr<Operator>;

}