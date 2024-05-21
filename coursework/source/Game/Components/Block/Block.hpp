#pragma once
#include "../Object.hpp"


enum class BlockType {
    //SPEED_INCREASE = 0,
    //SECOND_BALL,
    //SLIDER_WIDTH_INCREASE,
    //SlIDER_WIDTH_DECREASE,
    //SAFE_FLOOR,
    DEFAULT,
    EMPTY
};


class Block : public Object {
    int lifePoints;
    BlockType type;
public:
    Block(sf::Vector2f const& pos, float const size, int const lifePoints, BlockType const type);
    bool hit();
};
