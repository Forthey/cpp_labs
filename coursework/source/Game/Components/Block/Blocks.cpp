#include "Blocks.hpp"

#include <fstream>
#include <random>

#include "BonusBlock.hpp"
#include "DefaultBlock.hpp"
#include "InvulnerableBlock.hpp"
#include "JellyBlock.hpp"


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

    BonusType randomBonus;

    std::random_device rd;
    std::mt19937 randomGen(rd());
    std::uniform_int_distribution<> healthValue(1, 4);
    std::uniform_real_distribution<float> bonusValue(0.8f, 2.0f);
    std::uniform_real_distribution<float> bonusDuration(4.0f, 8.0f);
    std::uniform_int_distribution<> bonusDist(0, int(BonusType::SPEED_INCREASE) - 1);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (dataFile.eof()) {
                blocks.clear();
                return;
            }

            currentPos = { defaultPadding.x + x * blockSize, defaultPadding.y + y * blockSize };

            dataFile >> code;
            switch (code) {
            case 'e':
                break;
            case 'd':
                blocks.emplace_back(std::make_unique<DefaultBlock>(blockSize, currentPos, healthValue(randomGen)));
                break;
            case 'b':
                randomBonus = BonusType(bonusDist(randomGen));
                blocks.emplace_back(std::make_unique<BonusBlock>(
                    blockSize, 
                    currentPos, 
                    healthValue(randomGen), 
                    Bonus(randomBonus, bonusValue(randomGen), bonusDuration(randomGen))
                ));
                break;
            case 'i':
                blocks.emplace_back(std::make_unique<InvulnerableBlock>(blockSize, currentPos));
                break;
            case 'j':
                blocks.emplace_back(std::make_unique<JellyBlock>(blockSize, currentPos, bonusValue(randomGen)));
                break;
            default:
                blocks.clear();
                return;
            }
        }
    }

}

void Blocks::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto const& block : blocks) {
        target.draw(*block);
    }
}
