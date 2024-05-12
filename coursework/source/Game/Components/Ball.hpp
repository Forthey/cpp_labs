#pragma once
#include "../utility.hpp"


class Ball {
    // ед./сек.
    Vector speed;
    Point pos;
public:
    Ball(Point const& pos, Vector const& speed) : pos(pos), speed(speed) {}

    void inverseX() { speed.x = -speed.x; }
    void inverseY() { speed.y = -speed.y; }
    void move(float dt) {
        pos.x += speed.x * dt;
        pos.y += speed.y * dt;
    }

    Point const& getPos() const { return pos; }
};
