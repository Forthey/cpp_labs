#include <iostream>
#include <format>

#include "Calculator/Calculator.hpp"
#include "Calculator/FuncLoader/PluginsLoader.hpp"
#include "CLI.hpp"


int main() {
    PluginsLoader::loadFunctions();

    CLI::startInteraction();

    PluginsLoader::freePlugins();
	return 0;
}