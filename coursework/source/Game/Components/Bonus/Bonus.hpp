#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>

enum class BonusType {
    SLIDER_WIDTH_CHANGE = 0,
    BALL_SPEED_CHANGE,
    SlIDER_STICK_CHANGE,
    PROTECTED_FLOOR,
    NEW_BALL,
    POINTS,
    SPEED_INCREASE,
};


class Bonus {
    BonusType type;
    float const value;
    float expireTime;
public:
    Bonus(BonusType const type, float const value, float const expireTime) : type(type), value(value), expireTime(expireTime) {}
    
    void update(const float dt) { expireTime -= dt; }
    bool expired() const { return expireTime < 0.0f; }

    BonusType const getType() const { return type; }
    float const getValue() const { return value; }
};
