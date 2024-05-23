#pragma once

#include <SFML/Graphics.hpp>

#include "../../Game/Game.hpp"


class GameView : public sf::Drawable
{
	std::unique_ptr<Game> game;
	sf::Vector2u windowSize;
	sf::Vector2f gameViewSize;
	float gemViewSize = 0.0f;
	float const gameViewFill = 0.9f;

	std::unordered_map<GemType, sf::Color> gemTypeToColor = {
		{GemType::BLUE, sf::Color::Blue},
		{GemType::GREEN, sf::Color::Green},
		{GemType::RED, sf::Color::Red},
		{GemType::YELLOW, sf::Color::Yellow},
		{GemType::MAGENTA, sf::Color::Magenta},
		{GemType::CYAN, sf::Color::Cyan},
	};

	sf::Vector2i readParamsFromConf();
	sf::Vector2f transformGame(Point const& gamePoint) const;
	Point transformField(sf::Vector2i const& fieldPoint) const;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	GameView(sf::Vector2u const& windowSize);

	void restart();
	void update();
	void end();

	bool inView(sf::Vector2i const& mousePos) const;
	void onClick(sf::Vector2i const& mousePos);
};

