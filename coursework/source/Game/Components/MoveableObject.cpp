#include "MoveableObject.hpp"
#include <iostream>

MoveableObject::MoveableObject(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos, sf::Vector2f const& speed) : Object(textureName, size, pos), speed(speed) {
}

void MoveableObject::move(float const dt) {
    setPos({ getPos().x + speed.x * dt, getPos().y + speed.y * dt});
}

CollisionResult MoveableObject::checkCollision(sf::Vector2f const& pos, sf::Vector2f const& size)
{
    sf::Vector2f const thisCenter = { getPos().x + getSize().x / 2.0f, getPos().y + getSize().y / 2.0f };
    sf::Vector2f const thatCenter = { pos.x + size.x / 2.0f, pos.y + size.y / 2.0f };
    sf::Vector2f centerDiff = { std::abs(thisCenter.x - thatCenter.x) / size.x, std::abs(thisCenter.y - thatCenter.y) / size.y };

    bool top = pos.y < getPos().y + getSize().y && getPos().y + getSize().y < pos.y + size.y;
    bool bottom = pos.y < getPos().y && getPos().y < pos.y + size.y;
    bool left = pos.x < getPos().x + getSize().x && getPos().x + getSize().x < pos.x + size.x;
    bool right = pos.x < getPos().x && getPos().x < pos.x + size.x;

    if (left && (top || bottom) && centerDiff.y <= centerDiff.x) {
        setPos({ pos.x - getSize().x, getPos().y });
        inverseX();
        return CollisionResult::LEFT;
    }
    if (right && (top || bottom) && centerDiff.y <= centerDiff.x) {
        setPos({ pos.x + size.x, getPos().y });
        inverseX();
        return CollisionResult::RIGHT;
    }
    if (top && (left || right) && centerDiff.y >= centerDiff.x) {
        setPos({ getPos().x, pos.y - getSize().y });
        inverseY();
        return CollisionResult::TOP;
    }
    if (bottom && (left || right) && centerDiff.y >= centerDiff.x) {
        setPos({ getPos().x, pos.y + size.y });
        inverseY();
        return CollisionResult::BOTTOM;
    }

    return CollisionResult::NONE;
}
