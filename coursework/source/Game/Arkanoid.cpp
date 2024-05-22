#include "Arkanoid.hpp"

#include <iostream>


Arkanoid::Arkanoid(sf::Vector2u const& windowSize) :
    windowSize(windowSize)
{
    TextureManager::load();

    blocks = std::make_unique<Blocks>(windowSize, "levels/test.arknd");
    slider = std::make_unique<Slider>(windowSize);
    balls.emplace_back(std::make_unique<Ball>(windowSize));
    floor = std::make_unique<Floor>(windowSize);
    score = std::make_unique<Score>(windowSize);

    currentTime = timer.now();
}


void Arkanoid::update(float const x)
{
    float const dt = std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - currentTime).count() / 1000.0f;
    currentTime = timer.now();

    if (x >= 0 && x < windowSize.x - slider->getSize().x) {
        slider->setPosX(x, dt);
    }

    updateFallingBonuses(dt);
    updateActiveBonuses(dt);
    updateBalls(dt);
}

Arkanoid::~Arkanoid() {
    TextureManager::clear();
}


void Arkanoid::updateFallingBonuses(float const dt) {
    for (auto bonus = fallingBonuses.begin(); bonus != fallingBonuses.end(); ++bonus) {
        (*bonus)->move(dt);

        if ((*bonus)->wentOutOfField(windowSize)) {
            bonus = fallingBonuses.erase(bonus);
            if (bonus == fallingBonuses.end()) {
                break;
            }
            continue;
        }
        if (slider->catchedBonus(**bonus)) {
            std::shared_ptr<Bonus> newBonus = (*bonus)->getBonus();
            manageNewBonus(newBonus);

            fallingBonuses.erase(bonus);
            break;
        }
    }
}


void Arkanoid::updateActiveBonuses(float const dt) {
    for (auto bonus = activeBonuses.begin(); bonus != activeBonuses.end(); ++bonus) {
        (*bonus)->update(dt);
        if ((*bonus)->expired()) {
            resetBonus(*bonus);
            bonus = activeBonuses.erase(bonus);
            if (bonus == activeBonuses.end()) {
                break;
            }
        }
    }
}


void Arkanoid::updateBalls(float const dt) {
    for (auto& ball : balls) {
        ball->move(dt);
        switch (ball->checkCollisions(*blocks, fallingBonuses, balls, *slider, windowSize)) {
        case BallCollisionResult::FLOOR:
            if (!floor->isInvulnerable()) {
                score->updateScore(-1);
            }
            else {
                floor->removeInvulnerability();
            }
            break;
        case BallCollisionResult::BLOCK:
            score->updateScore(1);
            break;
        default: 
            break;
        }
    }
}

void Arkanoid::resetBonus(std::shared_ptr<Bonus>& bonus) {
    switch (bonus->getType())
    {
    case BonusType::SPEED_INCREASE:
        break;
    case BonusType::SLIDER_WIDTH_CHANGE:
        slider->setSize({ slider->getSize().x / bonus->getValue(), slider->getSize().y });
        break;
    case BonusType::BALL_SPEED_CHANGE:
        for (auto& ball : balls) {
            ball->setSpeed({ ball->getSpeed().x * bonus->getValue(), ball->getSpeed().y * bonus->getValue() });
        }
        break;
    case BonusType::SlIDER_STICK_CHANGE:
        slider->setStickyness(slider->getStickyness() / bonus->getValue());
        break;
    case BonusType::PROTECTED_FLOOR:
        break;
    default:
        break;
    }
}


void Arkanoid::manageNewBonus(std::shared_ptr<Bonus>& newBonus)
{
    switch (newBonus->getType())
    {
    case BonusType::SLIDER_WIDTH_CHANGE:
        slider->setSize({ slider->getSize().x * newBonus->getValue(), slider->getSize().y });
        break;
    case BonusType::BALL_SPEED_CHANGE:
        break;
    case BonusType::SlIDER_STICK_CHANGE:
        slider->setStickyness(slider->getStickyness() * newBonus->getValue());
        break;
    case BonusType::PROTECTED_FLOOR:
        floor->addInvulnerability();
        break;
    case BonusType::NEW_BALL:
        balls.emplace_back(std::make_unique<Ball>(
            windowSize, 
            sf::Vector2f(slider->getPos().x, slider->getPos().y - windowSize.x / 50.0f), 
            sf::Vector2f((0.2f + static_cast<float>(std::rand()) / RAND_MAX) / 2.0f * windowSize.x, -(0.2f + static_cast<float>(std::rand()) / RAND_MAX) / 2.0f * windowSize.y)));
        break;
    }

    activeBonuses.emplace_back(newBonus);
}


void Arkanoid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*blocks);

    target.draw(*slider);

    target.draw(*floor);

    target.draw(*score);

    for (auto const& bonus : fallingBonuses) {
        target.draw(*bonus);
    }

    for (auto const& ball : balls) {
        target.draw(*ball);
    }
}
