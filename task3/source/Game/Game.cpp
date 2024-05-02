#include "Game.hpp"

#include <stdexcept>
#include <algorithm>
#include <ranges>
#include <format>
#include <iostream>
#include <algorithm>
#include <queue>
#include <thread>



Game::Game(int width, int height)
{
	if (width == 0 || height == 0) {
		throw std::runtime_error("Игровое поле не может быть пустым");
	}

	std::function<GemType(FieldSize)> gen = [](FieldSize fieldSize) { return GemType(rand() % int(GemType::NONE)); };
	FieldSize fieldSize = { width, height };

	field = std::make_unique<GemsField>(fieldSize, gen);

	currentTime = timer.now();
}


GemsField const& Game::getGemsField()
{
	return *field;
}


bool Game::pointAdjacent(int x1, int y1, int x2, int y2)
{
	if (abs(x1 - x2) == 1 && y1 - y2 == 0) {
		return true;
	}
	if (abs(y1 - y2) == 1 && x1 - x2 == 0) {
		return true;
	}
	return false;
}


void Game::buildDuplSequence(std::vector<Point>& points, Point const& startPoint)
{
	std::unordered_map<long long, char> visited;
	std::queue<Point> queue;
	GemType searchType = field->at(startPoint).getType();

	queue.push(startPoint);

	Point point;
	while (!queue.empty()) {
		point = queue.front();
		queue.pop();

		if (!visited[point.y * field->getFieldSize().x + point.x] && field->at(point).getType() == searchType) {
			points.push_back(point);

			if (point.x < field->getFieldSize().x - 1) {
				queue.push({ std::min(point.x + 1, field->getFieldSize().x - 1), point.y });
			}
			if (point.x > 0) {
				queue.push({ std::max(point.x - 1, 0), point.y });
			}
			if (point.y < field->getFieldSize().y - 1) {
				queue.push({ point.x, std::min(point.y + 1, field->getFieldSize().y - 1) });
			}
			if (point.y > 0) {
				queue.push({ point.x, std::max(point.y - 1, 0) });
			}
		}
		visited[point.y * field->getFieldSize().x + point.x] = true;
	}
}


void Game::removeDuplicates(Point const& startPoint, std::vector<Point>& removedPoints)
{
	std::vector<Point> points;
	buildDuplSequence(points, startPoint);

	if (points.size() < 3 || field->at(startPoint).getType() == GemType::NONE) {
		return;
	}

	for (Point& point : points) {
		field->at(point) = Gem(GemType::NONE);
	}

	for (auto& point : points) {
		removedPoints.push_back(point);
	}
}


void Game::shiftGems()
{
	for (int y = field->getFieldSize().y - 1; y >= 0; y--) {
		for (int x = 0; x < field->getFieldSize().x; x++) {
			if (field->at(x, y).getType() == GemType::NONE) {
				for (int iterY = y; iterY < field->getFieldSize().y - 1; iterY++) {
					field->at(x, iterY) = field->at(x, iterY + 1);

					if (field->at(x, iterY).getType() != GemType::NONE) {
						if (std::ranges::find_if(
							changedGemPositions,
							[x, iterY](Point const& p) {
								return x == p.x && iterY == p.y;
							}
							) == changedGemPositions.end()) {
							changedGemPositions.push_back({ x, iterY });
						}
					}
				}

				field->at(x, field->getFieldSize().y - 1) = Gem(GemType::NONE);
			}
		}
	}
}


void Game::step()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - currentTime) < deltaTime) {
		return;
	}
	currentTime = timer.now();

	std::vector<GemPathWithType> removedPoints;

	switch (state)
	{
	case Game::State::DOING_DESTRUCTION:
		if (changedGemPositions.empty()) {
			state = State::WAITING_CLICK;
		}
		for (Point& point : changedGemPositions) {
			removedPoints.push_back({field->at(point).getType(), {}});
			removeDuplicates(point, removedPoints[removedPoints.size() - 1].path);
		}
		changedGemPositions.clear();
		procBonuses(removedPoints);
		shiftGems();
		break;
	default:
		break;
	}
}

void Game::onClick(Point const& point)
{
	onClick(point.x, point.y);
}

void Game::onClick(int x, int y)
{
	if (y < 0 || y >= field->getFieldSize().y || 
		x < 0 || x >= field->getFieldSize().x || 
		field->at(x, y).getType() == GemType::NONE) {
		return;
	}

	switch (state)
	{
	case State::WAITING_CLICK:
		activeGemPos = { x, y };
		field->at(x, y).setFocus(true);
		state = State::WAITING_SECOND_CLICK;
		break;
	case State::WAITING_SECOND_CLICK:
		if (activeGemPos.x == x && activeGemPos.y == y) {
			field->at(activeGemPos).setFocus(false);
			state = State::WAITING_CLICK;
		}
		else if (pointAdjacent(activeGemPos.x, activeGemPos.y, x, y)) {
			field->at(activeGemPos).setFocus(false);
			std::swap(field->at(activeGemPos), field->at(x, y));
			state = State::DOING_DESTRUCTION;

			changedGemPositions.push_back(activeGemPos);
			changedGemPositions.push_back({ x, y });
		}
		else {
			field->at(activeGemPos).setFocus(false);
			activeGemPos = { x, y };
			field->at({x, y}).setFocus(true);
		}
		break;
	case State::DOING_DESTRUCTION:
		break;
	default:
		break;
	}
}
