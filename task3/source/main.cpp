#include <iostream>
#include <unordered_map>

#include "WindowHandler/WindowHandler.hpp"


int main() {
	sf::RenderWindow rw(
		sf::VideoMode(
			2 * sf::VideoMode::getDesktopMode().width / 3,
			2 * sf::VideoMode::getDesktopMode().height / 3
		),
		"GEMS"
		// sf::Style::Fullscreen
	);

	WindowHandler WindowHandler(rw);

	WindowHandler.runMainLoop();
	return 0;
}