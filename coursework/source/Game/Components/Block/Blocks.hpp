#pragma once 
#include "Block.hpp"

#include <list>


class Blocks : public sf::Drawable {
    std::list<std::unique_ptr<Block>> blocks;

    float blockSize = 0;
    sf::Vector2f defaultPadding;

    sf::Texture texture;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Blocks(sf::Vector2u const& windowSize, std::string const& dataFileName);

    std::list<std::unique_ptr<Block>>& getBlocks() { return blocks; }
    float const getBlockSize() const { return blockSize; }
};