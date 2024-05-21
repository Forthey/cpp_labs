#include "Arkanoid.hpp"
#include <iostream>


Arkanoid::Arkanoid(sf::Vector2u const& windowSize) : windowSize(windowSize), blocks(windowSize, "levels/test.arknd")
{
    slider = std::make_unique<Slider>(windowSize);
    balls.emplace_back(windowSize);

    currentTime = timer.now();
}

void Arkanoid::update(float const x)
{
    float const dt = std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - currentTime).count() / 1000.0f;
    currentTime = timer.now();

    if (x >= slider->getSize().x && x < windowSize.x - slider->getSize().x) {
        slider->setPosX(x, dt);
    }
    for (Ball& ball : balls) {
        ball.move(dt);
        ball.checkCollisions(blocks, *slider, windowSize);
    }
}

void Arkanoid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(blocks);

    for (Ball const& ball : balls) {
        target.draw(ball);
    }

    target.draw(*slider);
}
