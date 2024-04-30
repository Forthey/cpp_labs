#pragma once
#include <memory>

#include "Field/GemsField.hpp"


class Game {
	enum class State {
		WAITING_CLICK,
		WAITING_SECOND_CLICK,
		DOING_DESTRUCTION
	};

	State state = State::WAITING_CLICK;
	Point activeGemPos = {-1, -1};
	std::vector<Point> changedGemPositions;
	std::unique_ptr<GemsField> field;

	static bool pointAdjacent(int x1, int y1, int x2, int y2);

	void buildDuplSequence(std::vector<Point>& points, Point const& startPoint);
	bool removeDuplicates(Point const& startPoint);
	void shiftGems();
public:
	explicit Game(int width, int height);
	void step();
	void onClick(Point const& point);
	void onClick(int x, int y);

	GemsField const& getGemsField();
};

