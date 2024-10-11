#include <iostream>
#include <format>

#include "Calculator/Calculator.hpp"
#include "Calculator/FuncLoader/FuncLoader.hpp"
#include "CLI.hpp"


int main() {
    FuncLoader::loadFunctions();

    CLI::startInteraction();

    FuncLoader::freeFuncs();
	return 0;
}