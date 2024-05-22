#pragma once
#include <format>

#include "BaseBlock.hpp"


class DefaultBlock : public BaseBlock {
protected:
    int lifePoints;

    DefaultBlock(std::string const& textureName, float const size, sf::Vector2f const& pos, int const lifePoints) :
        BaseBlock(textureName, size, pos), lifePoints(lifePoints) {}
public:
    DefaultBlock(float const size, sf::Vector2f const& pos, int const lifePoints) :
        BaseBlock(std::format("default_block_{}.png", std::max(1, std::min(4, lifePoints))), size, pos), lifePoints(lifePoints) {}

    std::shared_ptr<Bonus> const& hit() override { lifePoints--, setTexture(std::format("default_block_{}.png", std::max(1, std::min(4, lifePoints)))); return nullptr; }
    bool shouldBeDestroyed() override { return lifePoints <= 0; }
};

