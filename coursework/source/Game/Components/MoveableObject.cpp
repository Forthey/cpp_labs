#include "MoveableObject.hpp"

float const MoveableObject::maxSpeed = 1000.0f;

MoveableObject::MoveableObject(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos, sf::Vector2f const& speed) :
    Object(textureName, size, pos), speed(speed) {

};

void MoveableObject::move(float const dt) { 
    setPos({ getPos().x + speed.x * dt, getPos().y + speed.y * dt }); 
}
bool MoveableObject::wentOutOfField(sf::Vector2u fieldSize) const { 
    return getPos().x <= 0 || getPos().x >= fieldSize.x || getPos().y <= 0 || getPos().y >= fieldSize.y;
}

void MoveableObject::setSpeed(sf::Vector2f const& newSpeed) { 
    speed = { std::min(maxSpeed, newSpeed.x), std::min(maxSpeed, newSpeed.y) }; 
}

sf::Vector2f const& MoveableObject::getSpeed() const { 
    return speed;
}

void MoveableObject::changeSpeed(sf::Vector2f const& dv) {
    speed = { std::min(maxSpeed, speed.x + dv.x), std::min(maxSpeed, speed.y + dv.y) }; 
}