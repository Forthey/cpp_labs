#include "Object.hpp"

#include <iostream>
#include <format>


Object::Object(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos) : pos(pos), size(size) {
    if (!texture.loadFromFile(std::format("sprites/{}", textureName))) {
        std::cout << std::format("ERROR: Текстуры {} не существует\n", textureName);
        return;
    }
    sprite.setPosition(pos);
    sprite.scale({ size.x / texture.getSize().x, size.y / texture.getSize().y });
    sprite.setTexture(texture);
}

Object::Object(sf::Texture const& texture, sf::Vector2f const& size, sf::Vector2f const& pos) : pos(pos), size(size) {
    sprite.setPosition(pos);
    sprite.scale({ size.x / texture.getSize().x, size.y / texture.getSize().y });
    sprite.setTexture(texture);
}


void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite);
}