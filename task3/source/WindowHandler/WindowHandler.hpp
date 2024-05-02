#pragma once
#include <SFML/Graphics.hpp>

#include "Components/FpsBar.hpp"
#include "Components/GameView.hpp"
#include "Components/Menu.hpp"


class WindowHandler {
	// Windows
	sf::RenderWindow& window;
	// Components
	// Game
	GameView game;

	// FPS bar
	FpsBar fpsBar;

	// Menu
	Menu menu;
	
	void render();
public:
	explicit WindowHandler(sf::RenderWindow& window);
	void runMainLoop();
};


