#include "Score.hpp"

#include <iostream>
#include <format>


Score::Score(sf::Vector2u const& windowSize) {
    if (!font.loadFromFile("fonts/Jacquard12-Regular.ttf")) {
        std::cout << "Error loading font Jacquard12-Regular.ttf" << std::endl;
    }
    scoreText.setFont(font);
    scoreText.setString("Score: 0");
    scoreText.setCharacterSize(windowSize.y / 20);
    scoreText.setPosition({ 
        static_cast<float>(scoreText.getCharacterSize()),
        static_cast<float>(windowSize.y) - 2 * scoreText.getCharacterSize() });
}

void Score::updateScore(int newValue) {
    score += newValue;
    scoreText.setString(std::format("Score: {}", score));
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(scoreText);
}
