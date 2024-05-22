#pragma once
#include <SFML/Graphics.hpp>

#include "../MoveableObject.hpp"
#include "../Bonus/FallingBonus.hpp"


class Slider : public MoveableObject {
    float stickyness = 0.2f;

    float cachedIntervalLength = 0.0f;
    float const speedEvalIntervalSeconds = 0.01f;
    float deltaTime = 0.0f;
public:
    Slider(sf::Vector2u const& windowSize);

    bool catchedBonus(FallingBonus const& bonus) const;

    void setPosX(float const newX, float const dt);
    void setStickyness(float const newStickyness) { stickyness = std::max(1.0f, newStickyness); }
    float const getStickyness() const { return stickyness; }
};