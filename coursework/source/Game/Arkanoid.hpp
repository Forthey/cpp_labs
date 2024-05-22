#pragma once
#include <vector>
#include <chrono>

#include "TextureManager.hpp"

#include "Components/Block/Blocks.hpp"
#include "Components/Ball/Ball.hpp"
#include "Components/Slider/Slider.hpp"
#include "Components/Bonus/Bonus.hpp"
#include "Components/Bonus/FallingBonus.hpp"
#include "Components/Score/Score.hpp"
#include "Components/Floor/Floor.hpp"


class Arkanoid : public sf::Drawable {
    sf::Vector2u windowSize;

    std::unique_ptr<Blocks> blocks;

    std::list<std::unique_ptr<Ball>> balls;

    std::unique_ptr<Slider> slider;

    std::unique_ptr<Floor> floor;

    std::list<std::unique_ptr<FallingBonus>> fallingBonuses;
    std::list<std::shared_ptr<Bonus>> activeBonuses;

    std::unique_ptr<Score> score;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::chrono::high_resolution_clock timer;
    std::chrono::steady_clock::time_point currentTime;

    void updateFallingBonuses(float const dt);
    void updateActiveBonuses(float const dt);
    void updateBalls(float const dt);
    void resetBonus(std::shared_ptr<Bonus>& bonus);
    void manageNewBonus(std::shared_ptr<Bonus>& newBonus);
public:
    Arkanoid(sf::Vector2u const& windowSize);

    void update(float const x);

    ~Arkanoid();
};