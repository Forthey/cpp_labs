#pragma once
#include <SFML/Graphics.hpp>

#include "../Slider/Slider.hpp"
#include "../Block/Blocks.hpp"

#include "../MoveableObject.hpp"


enum class BallCollisionResult {
    CEIL,
    FLOOR,
    WALLS,
    BLOCK_VERTICAL,
    BLOCK_HORIZONTAL,
    SLIDER
};


class Ball : public MoveableObject {
    bool ceilCollided(sf::Vector2u const& windowSize);
    bool floorCollided(sf::Vector2u const& windowSize);
    bool wallsCollided(sf::Vector2u const& windowSize);
public:
    Ball(sf::Vector2u const& windowSize);

    BallCollisionResult checkCollisions(Blocks& blocks, Slider const& slider, sf::Vector2u const& windowSize);
};
