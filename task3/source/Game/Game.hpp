#pragma once
#include <memory>
#include <chrono>

#include "Field/GemsField.hpp"


class Game {
	enum class State {
		WAITING_CLICK,
		WAITING_SECOND_CLICK,
		DOING_DESTRUCTION
	};

	struct GemPathWithType {
		GemType type;
		std::vector<Point> path;
	};


	std::unique_ptr<GemsField> field;
	State state = State::WAITING_CLICK;
	Point activeGemPos = { -1, -1 };
	std::vector<Point> changedGemPositions;

	float const bonusProcChance = 1;
	int const vicinityRadius = 3;
	int const recolorGemCnt = 3;

	std::chrono::high_resolution_clock timer;
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::milliseconds deltaTime{2000};

	static bool pointAdjacent(int x1, int y1, int x2, int y2);

	void buildDuplSequence(std::vector<Point>& points, Point const& startPoint);
	void removeDuplicates(Point const& startPoint, std::vector<Point>& removedPoints);
	void shiftGems();
	void procBonuses(std::vector<GemPathWithType> const& removedPoints);
	void doRecolorBonus(Point const& point, GemType type);
	void doBombBonus(Point const& point);
public:
	explicit Game(int width, int height);
	void step();
	void onClick(Point const& point);
	void onClick(int x, int y);

	GemsField const& getGemsField();
};

