#pragma once
#include <chrono>

#include <SFML/Graphics.hpp>

#include "../Game/Game.hpp"
#include "Components/FpsBar.hpp"


class WindowHandler {
	// Windows
	sf::RenderWindow& window;
	// Components
	// Game
	std::unique_ptr<Game> game;
	sf::Vector2f gameViewSize;
	float gemViewSize;
	float const gameViewFill = 0.9f;

	// FPS bar
	FpsBar fpsBar;
	
	std::unordered_map<GemType, sf::Color> gemTypeToColor = {
		{GemType::BLUE, sf::Color::Blue},
		{GemType::GREEN, sf::Color::Green},
		{GemType::RED, sf::Color::Red},
		{GemType::YELLOW, sf::Color::Yellow},
		{GemType::MAGENTA, sf::Color::Magenta},
		{GemType::CYAN, sf::Color::Cyan},
	};

	sf::Vector2f transformGame(Point const& gamePoint);
	Point transformField(sf::Vector2i const& fieldPoint);
	bool inGameView(sf::Vector2i const& mousePos);
	void render();
public:
	explicit WindowHandler(sf::RenderWindow& window);
	void runMainLoop();
};


