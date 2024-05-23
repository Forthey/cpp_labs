#pragma once
#include "BaseBlock.hpp"

class JellyBlock : public BaseBlock {
    std::shared_ptr<Bonus> bounceBonus;
public:
    JellyBlock(float const size, sf::Vector2f const& pos, float const speedMul) : BaseBlock("jelly_block.png", size, pos) {
        bounceBonus = std::make_shared<Bonus>(BonusType::SPEED_INCREASE, speedMul, 5.0f);
    }

    std::shared_ptr<Bonus> const& hit() override { return bounceBonus; };
    bool shouldBeDestroyed() override { return false; };
};