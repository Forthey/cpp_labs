#include "Object.hpp"

#include <iostream>
#include <format>

#include "../TextureManager.hpp"


Object::Object(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos) : pos(pos), size(size) {
    texture = TextureManager::get(textureName);
    if (!texture) {
        return;
    }
    sprite.setPosition(pos);
    sprite.setScale({ size.x / texture->getSize().x, size.y / texture->getSize().y });
    sprite.setTexture(*texture);
}

void Object::setTexture(std::string const& textureKey) {
    if (!TextureManager::get(textureKey)) {
        return;
    }
    texture = TextureManager::get(textureKey);
    sprite.setTexture(*texture);
    sprite.setScale({ size.x / texture->getSize().x, size.y / texture->getSize().y });
}

void Object::setSize(sf::Vector2f const& newSize) {
    size = newSize;
    sprite.setScale({ size.x / texture->getSize().x, size.y / texture->getSize().y });
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}