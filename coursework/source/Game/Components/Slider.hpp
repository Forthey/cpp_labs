#pragma once
#include "../utility.hpp"


class Slider {
    float width;
    Point pos;
public:
    Slider(float const width, Point const& pos) : width(width), pos(pos) {};

    void setPosX(float newX) { pos.x = newX; }
};