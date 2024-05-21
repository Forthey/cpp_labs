#pragma once
#include <vector>
#include <chrono>

#include "Components/Block/Blocks.hpp"
#include "Components/Ball/Ball.hpp"
#include "Components/Slider/Slider.hpp"



class Arkanoid : public sf::Drawable {
    Blocks blocks;
    std::list<Ball> balls;
    std::unique_ptr<Slider> slider;

    sf::Vector2u windowSize;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::chrono::high_resolution_clock timer;
    std::chrono::steady_clock::time_point currentTime;
public:
    Arkanoid(sf::Vector2u const& windowSize);

    void update(float const x);
};