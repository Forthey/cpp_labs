#include "Ball.hpp"
#include <iostream>


Ball::Ball(sf::Vector2u const& windowSize) :
    CollideableObject(
        "ball.png", 
        { windowSize.x / 50.0f, windowSize.x / 50.0f }, 
        { windowSize.x * 0.5f, windowSize.y * 0.7f }, 
        { windowSize.x * 0.2f, windowSize.y * 0.4f }
    ), defaultSpeed({ std::abs(getSpeed().x), std::abs(getSpeed().y) }),
    decreaseDiffSpeed(getSpeed().x * 0.25f, getSpeed().y * 0.25f) {
}

Ball::Ball(sf::Vector2u const& windowSize, sf::Vector2f const& pos, sf::Vector2f const& speed) : 
    CollideableObject(
    "ball.png",
        { windowSize.x / 50.0f, windowSize.x / 50.0f },
        pos,
        speed
    ), defaultSpeed({ std::abs(getSpeed().x), std::abs(getSpeed().y) }),
    decreaseDiffSpeed(getSpeed().x * 0.25f, getSpeed().y * 0.25f) {
}


BallCollisionResult Ball::checkCollisions(
    Blocks& blocks, 
    std::list<std::unique_ptr<FallingBonus>>& fallingBonuses, 
    std::list<std::unique_ptr<Ball>>& balls,
    Slider const& slider, 
    sf::Vector2u const& windowSize
) {
    switch (checkCollision(slider.getPos(), slider.getSize()))
    {
    case CollisionResult::LEFT:
    case CollisionResult::RIGHT:
        changeSpeed({ slider.getSpeed().x, 0.0f });
        return BallCollisionResult::SLIDER;
    case CollisionResult::TOP:
    case CollisionResult::BOTTOM:
        changeSpeed({ slider.getSpeed().x * slider.getStickyness(), 0.0f});
        return BallCollisionResult::SLIDER;
    case CollisionResult::NONE:
        break;
    }

    float const rectSize = 10000.0f, rectPadding = 100.0f;
    // Ceil
    if (checkCollision({ -rectPadding, -rectSize }, { (float)windowSize.x + rectPadding, rectSize }) != CollisionResult::NONE) {
        return BallCollisionResult::CEIL;
    }
    // Floor 
    if (checkCollision({ -rectPadding, (float)windowSize.y }, { (float)windowSize.x + rectPadding, rectSize }) != CollisionResult::NONE) {
        return BallCollisionResult::FLOOR;
    }
    // WALLS
    if (checkCollision({ -rectSize, -rectPadding }, { rectSize, (float)windowSize.y + rectPadding }) != CollisionResult::NONE) {
        return BallCollisionResult::WALLS;
    }
    if (checkCollision({ (float)windowSize.x, -rectPadding }, { rectSize, (float)windowSize.y + rectPadding }) != CollisionResult::NONE) {
        return BallCollisionResult::WALLS;
    }

    for (auto& ball : balls) {
        if (ball->getPos() == getPos()) {
            continue;
        }
        switch (checkCollision(ball->getPos(), ball->getSize())) {
        case CollisionResult::LEFT:
        case CollisionResult::RIGHT:
        case CollisionResult::TOP:
        case CollisionResult::BOTTOM:
            return BallCollisionResult::BALL;
            break;
        }
    }

    std::shared_ptr<Bonus> hiddenBonus;
    for (auto block = blocks.getBlocks().begin(); block != blocks.getBlocks().end(); ++block) {
        CollisionResult result = checkCollision((*block)->getPos(), { blocks.getBlockSize(), blocks.getBlockSize() });

        switch (result) {
        case CollisionResult::LEFT:
        case CollisionResult::RIGHT:
        case CollisionResult::TOP:
        case CollisionResult::BOTTOM:
            hiddenBonus = (*block)->hit();       
            if (hiddenBonus) {
                switch (hiddenBonus->getType()) {
                case BonusType::SPEED_INCREASE:
                    if (result == CollisionResult::LEFT || result == CollisionResult::RIGHT) {
                        setSpeed({ getSpeed().x * hiddenBonus->getValue(), getSpeed().y });
                    }
                    else if (result == CollisionResult::TOP || result == CollisionResult::BOTTOM) {
                        setSpeed({ getSpeed().x, getSpeed().y * hiddenBonus->getValue() });
                    }                   
                    break;
                default:
                    fallingBonuses.emplace_back(std::make_unique<FallingBonus>((*block)->getPos(), (*block)->getSize(), windowSize.y / 10.0f, hiddenBonus));
                    break;
                }            
            }
            if ((*block)->shouldBeDestroyed()) {
                block = blocks.getBlocks().erase(block);
            }
            return BallCollisionResult::BLOCK;
        case CollisionResult::NONE:
            break;
        }
    }

    return BallCollisionResult::NONE;
}


inline int sign(float const x) {
    if (x > 0.0f) {
        return 1;
    }
    if (x < 0) {
        return -1;
    }
    return 0;
}

void Ball::move(float const dt)
{
    setPos({ getPos().x + getSpeed().x * dt, getPos().y + getSpeed().y * dt});

    sf::Vector2f dv;
    if (std::abs(getSpeed().x) > defaultSpeed.x) {
        dv.x += -sign(getSpeed().x) * decreaseDiffSpeed.x * dt;
    }
    else {
        dv.x += sign(getSpeed().x) * decreaseDiffSpeed.x * dt;
    }
    if (std::abs(getSpeed().y) > defaultSpeed.y) {
        dv.y += -sign(getSpeed().x) * decreaseDiffSpeed.y * dt;
    }
    else {
        dv.y += sign(getSpeed().x) * decreaseDiffSpeed.y * dt;
    }
    changeSpeed(dv);
}
