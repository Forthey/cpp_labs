#pragma once
#include "BaseBlock.hpp"

class InvulnerableBlock : public BaseBlock {
public:
    InvulnerableBlock(float const size, sf::Vector2f const& pos) : BaseBlock("invulnerable_block.png", size, pos) {}

    std::shared_ptr<Bonus> const& hit() override { return nullptr; };
    virtual bool shouldBeDestroyed() { return false; }
};

