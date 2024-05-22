#include "CollideableObject.hpp"

CollideableObject::CollideableObject(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos, sf::Vector2f const& speed) :
    MoveableObject(textureName, size, pos, speed) {
}

CollisionResult CollideableObject::checkCollision(sf::Vector2f const& objectPos, sf::Vector2f const& size)
{
    sf::Vector2f const thisCenter = { getPos().x + getSize().x / 2.0f, getPos().y + getSize().y / 2.0f };
    sf::Vector2f const thatCenter = { objectPos.x + size.x / 2.0f, objectPos.y + size.y / 2.0f };
    sf::Vector2f centerDiff = { std::abs(thisCenter.x - thatCenter.x) / size.x, std::abs(thisCenter.y - thatCenter.y) / size.y };

    bool top = objectPos.y < getPos().y + getSize().y && getPos().y + getSize().y < objectPos.y + size.y;
    bool bottom = objectPos.y < getPos().y && getPos().y < objectPos.y + size.y;
    bool left = objectPos.x < getPos().x + getSize().x && getPos().x + getSize().x < objectPos.x + size.x;
    bool right = objectPos.x < getPos().x && getPos().x < objectPos.x + size.x;

    if (left && (top || bottom) && centerDiff.y <= centerDiff.x) {
        setPos({ objectPos.x - getSize().x, getPos().y });
        inverseX();
        return CollisionResult::LEFT;
    }
    if (right && (top || bottom) && centerDiff.y <= centerDiff.x) {
        setPos({ objectPos.x + size.x, getPos().y });
        inverseX();
        return CollisionResult::RIGHT;
    }
    if (top && (left || right) && centerDiff.y >= centerDiff.x) {
        setPos({ getPos().x, objectPos.y - getSize().y });
        inverseY();
        return CollisionResult::TOP;
    }
    if (bottom && (left || right) && centerDiff.y >= centerDiff.x) {
        setPos({ getPos().x, objectPos.y + size.y });
        inverseY();
        return CollisionResult::BOTTOM;
    }

    return CollisionResult::NONE;
}