#pragma once
#include "../MoveableObject.hpp"
#include "../Bonus/Bonus.hpp"


class FallingBonus : public MoveableObject {
    std::shared_ptr<Bonus> bonus;
public:
    FallingBonus(sf::Vector2f const& pos, sf::Vector2f const& size, float const speed, std::shared_ptr<Bonus> const& bonus) :
        MoveableObject("bonus.png", size, pos, { 0.0f, speed }), bonus(bonus) {}

    std::shared_ptr<Bonus> const& getBonus() const { return bonus; }
};