#pragma once
#include <SFML/Graphics.hpp>


class Ball : public sf::Drawable {
    // ед./сек.
    sf::Vector2f speed;
    sf::Vector2f pos;

    sf::CircleShape ball;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Ball(sf::Vector2u const& windowSize);

    bool ceilCollided(sf::Vector2u const& windowSize);
    bool floorCollided(sf::Vector2u const& windowSize);
    bool wallsCollided(sf::Vector2u const& windowSize);
    bool topBottomCollided(sf::Vector2f const& blockPos, float const size);
    bool leftRightCollided(sf::Vector2f const& blockPos, float const size);
    bool sliderCollided(sf::Vector2f const& sliderPos, sf::Vector2f const& sliderSize);

    void inverseX();
    void inverseY();
    void move(float dt);

    sf::Vector2f const& getPos() const { return pos; }
};
