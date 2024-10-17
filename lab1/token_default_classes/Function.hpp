#pragma once
#include "PrefixOperator.hpp"


namespace Tok {

    class Function : public PrefixOperator {
    public:
        explicit Function(std::string const &name, std::function<double(std::vector<double> const &)>& calcFunc)
                : PrefixOperator(name, DEFAULT_FUNCTION_PRIORITY, calcFunc) {}
    };

}