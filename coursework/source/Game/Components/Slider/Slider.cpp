#include "Slider.hpp"

#include <iostream>
#include <format>


Slider::Slider(sf::Vector2u const& windowSize) : MoveableObject("slider.png", { windowSize.x / 10.0f, windowSize.y / 50.0f }, { windowSize.x * 0.5f, windowSize.y * 0.9f }, { 0, 0 }) {
}

void Slider::setPosX(float const newX, float const dt) {
    cachedIntervalLength += newX - getPos().x;
    deltaTime += dt;
    if (deltaTime > speedEvalIntervalSeconds) {
        setSpeed({ cachedIntervalLength / deltaTime, 0.0f });
        cachedIntervalLength = 0;
        deltaTime = 0;
    }
    setPos({ newX, getPos().y });
}

bool Slider::catchedBonus(FallingBonus const& bonus) const {
    sf::Vector2f centerDiff(
        std::abs(bonus.getPos().x + bonus.getSize().x * 0.5f - getPos().x - getSize().x * 0.5f),
        std::abs(bonus.getPos().y + bonus.getSize().y * 0.5f - getPos().y - getSize().y * 0.5f)
    );

    return centerDiff.y < (bonus.getSize().y + getSize().y) * 0.5f && centerDiff.x < (bonus.getSize().x + getSize().x) * 0.5f;
}
