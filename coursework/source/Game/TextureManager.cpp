#include "TextureManager.hpp"

#include <filesystem>
#include <iostream>
#include <format>


std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::textures;


std::string getNameFromPath(std::string const& path) {
    int i = 0;
    while (path[i] != '\\') {
        i++;
    }
    i++;
    return std::move(path.substr(i));
}
void TextureManager::load() {
    std::string path = "textures";
    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(entry.path().string())) {
            continue;
        }
        std::string const textureName = std::move(getNameFromPath(entry.path().string()));
        textures[textureName] = texture;
    }
}

std::shared_ptr<sf::Texture> const& TextureManager::get(std::string const& key)
{
    if (!textures.contains(key)) {
        std::cout << std::format("ERROR: Текстуры {} не существует\n", key);
        return nullptr;
    }

    return textures[key];
}

void TextureManager::clear() {
    textures.clear();
}
