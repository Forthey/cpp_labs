#include "Slider.hpp"

#include <iostream>
#include <format>


Slider::Slider(sf::Vector2u const& windowSize) : size(windowSize.x / 10.0f, windowSize.y / 100.0f), pos(windowSize.x * 0.5f, windowSize.y * 0.9f), rect(size) {
    rect.setPosition({ pos.x - size.x / 2.0f, pos.y + size.y / 2.0f });
}

void Slider::setPosX(float newX) {
    pos.x = newX;
    rect.setPosition({ pos.x - size.x / 2.0f, pos.y + size.y / 2.0f });
}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rect);
}
