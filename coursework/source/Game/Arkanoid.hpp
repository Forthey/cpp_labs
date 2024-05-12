#pragma once
#include <vector>

#include "Components/Ball.hpp"
#include "Components/Block.hpp"
#include "Components/Slider.hpp"



class Arkanoid {
    std::vector<std::vector<Block>> blocks;
    std::vector<Ball> balls;

    Slider slider;


public:
    void start();
    void update();
    void end();
};