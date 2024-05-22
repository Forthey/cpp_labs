#pragma once
#include <SFML/Graphics.hpp>

#include <map>
#include <string>


class TextureManager {
    static std::map<std::string, std::shared_ptr<sf::Texture>> textures;
public:
    static void load();
    static std::shared_ptr<sf::Texture> const& get(std::string const& key);
    static void clear();
};

