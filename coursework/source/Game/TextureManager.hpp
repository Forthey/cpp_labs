#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <string>


class TextureManager {
    static std::map<std::string, std::shared_ptr<sf::Texture>> textures;
public:
    static void reload();
    static std::shared_ptr<sf::Texture> const& get(std::string const& key);
};

