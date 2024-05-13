#pragma once
#include "Game/Arkanoid.hpp"


class WindowHandler {
    std::unique_ptr<sf::RenderWindow> window;
    std::unique_ptr<Arkanoid> arkanoid;
public:
    WindowHandler(sf::Vector2f const& screenFill = { 0.7f, 0.7f });
    void runMainLoop();
};

