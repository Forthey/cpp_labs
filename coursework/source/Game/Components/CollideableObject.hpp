#pragma once
#include "MoveableObject.hpp"


class CollideableObject : public MoveableObject {
    void inverseY() { setSpeed({ getSpeed().x, -getSpeed().y }); }
    void inverseX() { setSpeed({ -getSpeed().x, getSpeed().y }); }
public:
    CollideableObject(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos, sf::Vector2f const& speed);

    CollisionResult checkCollision(sf::Vector2f const& pos, sf::Vector2f const& size);
};

