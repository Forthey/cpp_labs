#pragma once
#include <SFML/Graphics.hpp>


class Object : public sf::Drawable {
private:
    sf::Vector2f size;
    // Позиция левого верхнего угла 
    sf::Vector2f pos;

    std::shared_ptr<sf::Texture> texture;
    sf::Sprite sprite;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Object(std::string const& textureName, sf::Vector2f const& size, sf::Vector2f const& pos);
    Object(sf::Texture const& texture, sf::Vector2f const& size, sf::Vector2f const& pos);

    void setTexture(std::string const& textureKey);
    void setSize(sf::Vector2f const& newSize);
    sf::Vector2f const& getSize() const { return size; }
    void setPos(sf::Vector2f const& pos) { this->pos = pos; sprite.setPosition(pos); };
    sf::Vector2f const& getPos() const { return pos; }
};

