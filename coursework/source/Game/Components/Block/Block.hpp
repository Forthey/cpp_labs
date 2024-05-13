#pragma once
#include <SFML/Graphics.hpp>


enum class BlockType {
    //SPEED_INCREASE = 0,
    //SECOND_BALL,
    //SLIDER_WIDTH_INCREASE,
    //SlIDER_WIDTH_DECREASE,
    //SAFE_FLOOR,
    DEFAULT,
    EMPTY
};


class Block : public sf::Drawable {
    int lifePoints;
    BlockType type;
    sf::Vector2f pos;

    sf::RectangleShape block;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Block(sf::Vector2f const& pos, float const size, int const lifePoints, BlockType const type);
    bool hit();

    sf::Vector2f const& getPos() const { return pos; }
};
