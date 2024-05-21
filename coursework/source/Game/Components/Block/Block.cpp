#include "Block.hpp"

#include <unordered_map>
#include <iostream>

Block::Block(sf::Vector2f const& pos, float const size, int const lifePoints, BlockType const type) : Object("default_block.png", {size, size}, pos), lifePoints(lifePoints), type(type) {
}

bool Block::hit()
{
    lifePoints--;
    return lifePoints <= 0;
}
