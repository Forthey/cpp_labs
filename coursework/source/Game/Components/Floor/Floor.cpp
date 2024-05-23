#include "Floor.hpp"

Floor::Floor(sf::Vector2u const& windowSize) : 
    Object("floor.png", { static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) * 0.01f }, {0, static_cast<float>(windowSize.y) * 0.99f}) {
}

bool Floor::isInvulnerable()
{
    return invulnerableFloorCount > 0;
}

void Floor::addInvulnerability() {
    invulnerableFloorCount++;
    if (invulnerableFloorCount == 1) {
        setTexture("floor_protected.png");
    }
}

void Floor::removeInvulnerability() {
    invulnerableFloorCount = std::max(0, --invulnerableFloorCount);
    if (invulnerableFloorCount == 0) {
        setTexture("floor.png");
    }
}
