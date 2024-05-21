#include "Slider.hpp"

#include <iostream>
#include <format>


Slider::Slider(sf::Vector2u const& windowSize) : Object("slider.png", { windowSize.x / 10.0f, windowSize.y / 50.0f }, { windowSize.x * 0.5f, windowSize.y * 0.9f }) {
}

void Slider::setPosX(float const newX, float const dt) {
    cachedIntervalLength += newX - getPos().x;
    deltaTime += dt;
    if (deltaTime > speedEvalIntervalSeconds) {
        avgSpeed = cachedIntervalLength / deltaTime;
        cachedIntervalLength = 0;
        deltaTime = 0;
    }
    setPos({ newX, getPos().y });
}
