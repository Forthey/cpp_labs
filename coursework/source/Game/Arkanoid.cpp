#include "Arkanoid.hpp"
#include <iostream>


Arkanoid::Arkanoid(sf::Vector2u const& windowSize) : windowSize(windowSize), blocks(windowSize, "levels/test.arknd")
{
    slider = std::make_unique<Slider>(windowSize);
    balls.emplace_back(windowSize);

    currentTime = timer.now();
}


void Arkanoid::checkCollision(Ball& ball, Blocks& blocks, Slider const& slider, sf::Vector2u const& windowSize)
{
    if (ball.sliderCollided(slider.getPos(), slider.getSize())) {
        ball.inverseY();
        return;
    }

    if (ball.ceilCollided(windowSize)) {
        ball.inverseY();
        return;
    }

    if (ball.wallsCollided(windowSize)) {
        ball.inverseX();
        return;
    }

    if (ball.floorCollided(windowSize)) {
        // TODO потеря очков
        ball.inverseY();
        return;
    }

    for (auto block = blocks.getBlocks().begin(); block != blocks.getBlocks().end(); ++block) {
        if (ball.topBottomCollided(block->getPos(), blocks.getBlockSize())) {
            ball.inverseY();
            if (block->hit()) {
                block = blocks.getBlocks().erase(block);
            }
            break;
        }

        if (ball.leftRightCollided(block->getPos(), blocks.getBlockSize())) {
            ball.inverseX();
            if (block->hit()) {
                block = blocks.getBlocks().erase(block);
            }
            break;
        }
    }
}

void Arkanoid::update(float const x)
{
    float const dt = std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - currentTime).count() / 1000.0f;
    currentTime = timer.now();

    slider->setPosX(x);
    for (Ball& ball : balls) {
        ball.move(dt);
        checkCollision(ball, blocks, *slider, windowSize);
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
