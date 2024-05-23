#pragma once
#include "../Object.hpp"
#include "../Bonus/Bonus.hpp"


class BaseBlock : public Object {
public:
    BaseBlock(std::string const& textureName, float const size, sf::Vector2f const& pos) : Object(textureName, { size, size }, pos) {}

    virtual std::shared_ptr<Bonus> const& hit() = 0;
    virtual bool shouldBeDestroyed() = 0;
};

