#pragma once
#include "../Object.hpp"


class Floor : public Object {
    int invulnerableFloorCount = 0;
public:
    Floor(sf::Vector2u const& windowSize);

    bool isInvulnerable();
    void addInvulnerability();
    void removeInvulnerability();
};

