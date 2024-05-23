#pragma once
#include <SFML/Graphics.hpp>

class Score : public sf::Drawable {
    int score = 0;

    sf::Font font;
    sf::Text scoreText;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Score(sf::Vector2u const& windowSize);

    void updateScore(int newValue);
};

