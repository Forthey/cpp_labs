#pragma once
#include <SFML/Graphics.hpp>


class Slider : public sf::Drawable {
    sf::Vector2f size;
    sf::Vector2f pos;

    sf::RectangleShape rect;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Slider(sf::Vector2u const& windowSize);

    sf::Vector2f const& getPos() const { return pos; }
    sf::Vector2f const& getSize() const { return size; }
    void setPosX(float newX);
};