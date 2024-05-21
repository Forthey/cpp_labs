#include <unordered_map>
#include <fstream>
#include <iostream>

#include "Block.hpp"
#include "Blocks.hpp"


std::unordered_map<char, BlockType> const codeToType = {
    { 'e', BlockType::EMPTY },
    { 'd', BlockType::DEFAULT }
};


Blocks::Blocks(sf::Vector2u const& windowSize, std::string const& dataFileName) : defaultPadding(windowSize.x / 100.0f, windowSize.y / 100.0f) {
    std::ifstream dataFile(dataFileName);

    if (!dataFile.is_open()) {
        return;
    }

    int width, height;
    if (!(dataFile >> width >> height)) {
        return;
    }

    blockSize = (windowSize.x - 2.0f * defaultPadding.x) / width;
    sf::Vector2f currentPos = defaultPadding;
    char code;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (dataFile.eof()) {
                blocks.clear();
                return;
            }
            dataFile >> code;
            if (codeToType.at(code) == BlockType::EMPTY) {
                continue;
            }
            currentPos = { defaultPadding.x + x * blockSize, defaultPadding.y + y * blockSize };
            blocks.emplace_back(std::make_unique<Block>(currentPos, blockSize, 1, codeToType.at(code)));
        }
    }
}

void Blocks::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto const& block : blocks) {
        target.draw(*block);
    }
}
