#pragma once
#include <SFML/Graphics.hpp>

#include "../MoveableObject.hpp"


class Slider : public Object {
    float avgSpeed = 0.0f;

    float cachedIntervalLength = 0.0f;
    float const speedEvalIntervalSeconds = 0.1f;
    float deltaTime = 0.0f;
public:
    Slider(sf::Vector2u const& windowSize);
    void setPosX(float const newX, float const dt);

    float const getSpeed() const { return avgSpeed; }
};