#pragma once
#include <SFML/Graphics.hpp>

#include "../Slider/Slider.hpp"
#include "../Block/Blocks.hpp"
#include "../Bonus/FallingBonus.hpp"

#include "../CollideableObject.hpp"


enum class BallCollisionResult {
    CEIL,
    FLOOR,
    WALLS,
    BLOCK,
    SLIDER,
    BALL,
    NONE
};


class Ball : public CollideableObject {
    sf::Vector2f const defaultSpeed;
    sf::Vector2f const decreaseDiffSpeed;
public:
    Ball(sf::Vector2u const& windowSize);
    Ball(sf::Vector2u const& windowSize, sf::Vector2f const& pos, sf::Vector2f const& speed);

    BallCollisionResult checkCollisions(
        Blocks& blocks,
        std::list<std::unique_ptr<FallingBonus>>& fallingBonuses,
        std::list<std::unique_ptr<Ball>>& balls,
        Slider const& slider, 
        sf::Vector2u const& windowSize
    );

    void move(float const dt) override;
};
