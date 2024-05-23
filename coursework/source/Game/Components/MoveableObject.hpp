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
    static float const maxSpeed;

    sf::Vector2f speed;
public:
    MoveableObject(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos, sf::Vector2f const& speed);

    virtual void move(float const dt);
    bool wentOutOfField(sf::Vector2u fieldSize) const;

    void setSpeed(sf::Vector2f const& newSpeed);
    sf::Vector2f const& getSpeed() const;
    void changeSpeed(sf::Vector2f const& dv);
};
