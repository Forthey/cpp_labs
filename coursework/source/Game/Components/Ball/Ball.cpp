#include "Ball.hpp"
#include <iostream>

#include <ranges>

Ball::Ball(sf::Vector2u const& windowSize) : MoveableObject("ball.png", { windowSize.x / 50.0f, windowSize.x / 50.0f }, { windowSize.x * 0.5f, windowSize.y * 0.7f }, { windowSize.x * 0.2f, windowSize.y * 0.4f }) {
}

bool Ball::ceilCollided(sf::Vector2u const& windowSize) {
    return getPos().y <= 0;
}

bool Ball::floorCollided(sf::Vector2u const& windowSize) {
    return getPos().y + getSize().y >= windowSize.y;
}

bool Ball::wallsCollided(sf::Vector2u const& windowSize) {
    return getPos().x - getSize().x <= 0 || getPos().x + getSize().x >= windowSize.x;
}


BallCollisionResult Ball::checkCollisions(Blocks& blocks, Slider const& slider, sf::Vector2u const& windowSize) {
    switch (checkCollision(slider.getPos(), slider.getSize()))
    {
    case CollisionResult::LEFT:
    case CollisionResult::RIGHT:
        return BallCollisionResult::SLIDER;
        break;
    case CollisionResult::TOP:
    case CollisionResult::BOTTOM:
        changeSpeed({ slider.getSpeed() / 3.0f, 0.0f });
        return BallCollisionResult::SLIDER;
        break;
    case CollisionResult::NONE:
        break;
    }

    // Ceil
    if (checkCollision({ 0.0f, -100.0f }, { (float)windowSize.x, 100.0f }) != CollisionResult::NONE) {
        return BallCollisionResult::CEIL;
    }
    // Floor 
    if (checkCollision({ 0.0f, (float)windowSize.y }, { (float)windowSize.x, 100.0f }) != CollisionResult::NONE) {
        return BallCollisionResult::FLOOR;
    }
    // WALLS
    if (checkCollision({ -100.0f, 0.0f }, { 100.0f, (float)windowSize.y }) != CollisionResult::NONE) {
        return BallCollisionResult::WALLS;
    }
    if (checkCollision({ (float)windowSize.x, 0.0f }, { 100.0f, (float)windowSize.y }) != CollisionResult::NONE) {
        return BallCollisionResult::WALLS;
    }

    for (auto block = blocks.getBlocks().begin(); block != blocks.getBlocks().end(); ++block) {
        switch (checkCollision((*block)->getPos(), { blocks.getBlockSize(), blocks.getBlockSize() })) {
        case CollisionResult::LEFT:
        case CollisionResult::RIGHT:
            if ((*block)->hit()) {
                block = blocks.getBlocks().erase(block);
            }
            return BallCollisionResult::BLOCK_HORIZONTAL;
            break;
        case CollisionResult::TOP:
        case CollisionResult::BOTTOM:
            if ((*block)->hit()) {
                block = blocks.getBlocks().erase(block);
            }
            return BallCollisionResult::BLOCK_VERTICAL;
            break;
        case CollisionResult::NONE:
            break;
        }
    }

    return BallCollisionResult::CEIL;
}