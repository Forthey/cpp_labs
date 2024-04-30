#include "Game.hpp"

#include <stdexcept>
#include <algorithm>
#include <ranges>
#include <format>
#include <iostream>
#include <algorithm>


GemsField const& Game::getGemsField()
{
	return *field;
}

bool Game::pointAdjacent(int x1, int y1, int x2, int y2)
{
	std::cout << std::format("x1={}, y1={}, x2={}, y2={}", x1, y1, x2, y2) << std::endl;
	if (abs(x1 - x2) == 1 && y1 - y2 == 0) {
		return true;
	}
	if (abs(y1 - y2) == 1 && x1 - x2 == 0) {
		return true;
	}
	return false;
}

Game::Game(int width, int height)
{
	if (width == 0 || height == 0) {
		throw std::runtime_error("Игровое поле не может быть пустым");
	}

	std::function<GemType(FieldSize)> gen = [](FieldSize fieldSize) { return GemType(rand() % int(GemType::TYPE_CNT)); };
	FieldSize fieldSize = { width, height };

	field = std::make_unique<GemsField>(fieldSize, gen);
}


void Game::step()
{
	switch (state)
	{
	case Game::State::DOING_DESTRUCTION:
		// TODO: рекурсивно искать последовательности для разрушения, возвращать что-то, если нашел, и менять состояние на дефолт, если ничего не найдено
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
	if (y < 0 || y >= field->getFieldSize().y || x < 0 || x >= field->getFieldSize().x) {
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
			state = State::WAITING_CLICK;
			//state = State::DOING_DESTRUCTION;
		}
		break;
	case State::DOING_DESTRUCTION:
		break;
	default:
		break;
	}
}
