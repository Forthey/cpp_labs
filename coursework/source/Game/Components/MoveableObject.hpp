#pragma once
#include "Object.hpp"


enum class CollisionResult {
    NONE,
    LEFT,
    RIGHT,
    TOP,
    BOTTOM
};


class MoveableObject : public Object {
private:
    sf::Vector2f speed;

    void inverseY() { speed.y = -speed.y; }
    void inverseX() { speed.x = -speed.x; }
public:
    MoveableObject(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos, sf::Vector2f const& speed);

    void move(float const dt);
    void changeSpeed(sf::Vector2f const& dv) { speed.x += dv.x, speed.y += dv.y; }

    CollisionResult checkCollision(sf::Vector2f const& pos, sf::Vector2f const& size);
};

