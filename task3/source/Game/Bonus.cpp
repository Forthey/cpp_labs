#include "Game.hpp"

#include <iostream>
#include <format>


void Game::procBonuses(std::vector<GemPathWithType> const& removedPoints) {
	std::uniform_real_distribution<float> distProcChance(0.0f, 1.0f);
	std::uniform_int_distribution<std::mt19937::result_type> distProcType(0, 1);

	for (auto& removedPath : removedPoints) {
		for (auto& removedPoint : removedPath.path) {
			if (distProcChance(rng) < bonusProcChance) {
				switch (distProcType(rng)) {
				case 0:
					std::cout << "Recolor!!!" << std::endl;
					doRecolorBonus(removedPoint, removedPath.type);
					break;
				case 1:
					std::cout << "Bomb!!!" << std::endl;
					doBombBonus(removedPoint);
					break;
				}
			}
		}
	}
}

inline bool locatedNearby(Point const& point1, Point const& point2) {
	int dx = std::abs(point1.x - point2.x);
	int dy = std::abs(point1.y - point2.y);
	return (dy <= 1 && dx == 0) || (dy == 0 && dx <= 1);
}


void Game::doRecolorBonus(Point const& point, GemType type) {
	std::vector<Point> vicinity;

	int yMin = std::max(point.y - vicinityRadius, 0);
	int yMax = std::min(point.y + vicinityRadius, field->getFieldSize().y - 1);
	int xMin = std::max(point.x - vicinityRadius, 0);
	int xMax = std::min(point.x + vicinityRadius, field->getFieldSize().x - 1);

	for (int y = yMin; y <= yMax; y++) {
		for (int x = xMin; x <= xMax; x++) {
			if (field->at({x, y}).getType() == GemType::NONE) {
				continue;
			}
			vicinity.emplace_back(x, y);
		}
	}

	for (int i = 0; i < recolorGemCnt && vicinity.size() != 0; i++) {
		std::uniform_int_distribution<std::mt19937::result_type> dist(0, int(vicinity.size()) - 1);
		Point point = vicinity[dist(rng)];
		for (auto iter = vicinity.begin(); iter != vicinity.end();) {
			if (locatedNearby(*iter, point)) {
				iter = vicinity.erase(iter);
			} 
			else {
				++iter;
			}
		}

		std::cout << std::format("Recolored ({}, {}) {} -> {}\n", point.x, point.y, int(field->at(point).getType()), int(type));
		field->at(point) = Gem(type);
		changedGemPositions.push_back(point);
	}
}


void Game::doBombBonus(Point const& point) {
	std::uniform_int_distribution<std::mt19937::result_type> distX(0, field->getFieldSize().x - 1);
	std::uniform_int_distribution<std::mt19937::result_type> distY(0, field->getFieldSize().y - 1);
	for (int i = 0; i < 5; i++) {
		int x = distX(rng);
		int y = distY(rng);

		std::cout << std::format("Blowed up ({}, {})\n", x, y);
		field->at({ x, y }) = Gem(GemType::NONE);
		changedGemPositions.push_back({ x, y });
	}
}
