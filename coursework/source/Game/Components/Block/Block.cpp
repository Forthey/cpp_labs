#include "Block.hpp"

#include <unordered_map>
#include <iostream>

static std::unordered_map<BlockType, sf::Color> const typeToColor = {
    { BlockType::DEFAULT, sf::Color::White }
};


Block::Block(sf::Vector2f const& pos, float const size, int const lifePoints, BlockType const type) : pos(pos), lifePoints(lifePoints), type(type), block({ size, size }) {
    block.setPosition(pos);
    block.setFillColor(typeToColor.at(type));
}

bool Block::hit()
{
    lifePoints--;
    return lifePoints <= 0;
}


void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(block);
}