#pragma once 
#include "Block.hpp"

#include <list>


class Blocks : public sf::Drawable {
    std::list<Block> blocks;

    float blockSize = 0;
    sf::Vector2f defaultPadding;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Blocks(sf::Vector2u const& windowSize, std::string const& dataFileName);

    std::list<Block>& getBlocks() { return blocks; }
    float const getBlockSize() const { return blockSize; }
};