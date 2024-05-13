#include "Ball.hpp"
#include <iostream>

#include <ranges>

Ball::Ball(sf::Vector2u const& windowSize) : pos(windowSize.x * 0.5f, windowSize.y * 0.7f), speed(windowSize.x * 0.1f, windowSize.y * 0.2f), ball(windowSize.x / 200.0f, 50) {
    ball.setPosition({ pos.x - ball.getRadius(), pos.y});
}

void Ball::inverseX() {
    speed.x = -speed.x;
    move(0.01f);
}

void Ball::inverseY() {
    speed.y = -speed.y;
    move(0.01f);
}

void Ball::move(float const dt) {
    pos.x += speed.x * dt;
    pos.y += speed.y * dt;

    ball.setPosition({ pos.x - ball.getRadius(), pos.y });
}

bool Ball::ceilCollided(sf::Vector2u const& windowSize) {
    return pos.y - ball.getRadius() <= 0;
}

bool Ball::floorCollided(sf::Vector2u const& windowSize) {
    return pos.y + ball.getRadius() >= windowSize.y;
}

bool Ball::wallsCollided(sf::Vector2u const& windowSize) {
    return pos.x - ball.getRadius() <= 0 || pos.x + ball.getRadius() >= windowSize.x;
}

bool Ball::topBottomCollided(sf::Vector2f const& blockPos, float const size) {
    return
        pos.y + ball.getRadius() > blockPos.y &&
        pos.y - ball.getRadius() < blockPos.y + size &&
        blockPos.x < pos.x && pos.x < blockPos.x + size;
}

bool Ball::leftRightCollided(sf::Vector2f const& blockPos, float const size) {
    return
        pos.x + ball.getRadius() > blockPos.x && 
        pos.x - ball.getRadius() < blockPos.x + size &&
        blockPos.y < pos.y && pos.y < blockPos.y + size;
}

bool Ball::sliderCollided(sf::Vector2f const& sliderPos, sf::Vector2f const& sliderSize) {
    return
        sliderPos.y - sliderSize.y / 2.0f < pos.y + ball.getRadius() && pos.y - ball.getRadius() < sliderPos.y + sliderSize.y / 2.0f && 
        sliderPos.x - sliderSize.x / 2.0f < pos.x && pos.x < sliderPos.x + sliderSize.x / 2.0f;
}



void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(ball);
}
