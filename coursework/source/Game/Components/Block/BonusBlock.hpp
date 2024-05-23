#pragma once
#include "DefaultBlock.hpp"


class BonusBlock : public DefaultBlock {
protected:
    std::shared_ptr<Bonus> hiddenBonus;
public:
    BonusBlock(float const size, sf::Vector2f const& pos, int const lifePoints, Bonus const& bonus) :
        DefaultBlock(std::format("bonus_block_{}.png", std::max(1, std::min(4, lifePoints))), size, pos, lifePoints), hiddenBonus{ std::make_shared<Bonus>(bonus) } {}

    std::shared_ptr<Bonus> const& hit() override { lifePoints--, setTexture(std::format("bonus_block_{}.png", std::max(1, std::min(4, lifePoints)))); return hiddenBonus; };
};
