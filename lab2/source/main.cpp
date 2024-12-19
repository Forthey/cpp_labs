#pragma execution_character_set( "utf-8" )

#include <clocale>
#include <windows.h>

#include "EngineTest.h"




int main() {
    SetConsoleOutputCP( 65001 );
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    EngineTest::testCommands();
}
