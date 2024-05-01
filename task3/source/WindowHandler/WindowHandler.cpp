#include "WindowHandler.hpp"

#include <iostream>


WindowHandler::WindowHandler(sf::RenderWindow& window) : window(window), fpsBar(window.getSize()) {
	game = std::make_unique<Game>(5, 5);

	gemViewSize = gameViewFill * window.getSize().y / game->getGemsField().getFieldSize().y;

	gameViewSize = {
		gemViewSize * game->getGemsField().getFieldSize().x,
		gemViewSize * game->getGemsField().getFieldSize().y
	};
}


sf::Vector2f WindowHandler::transformGame(Point const& gamePoint) {
	return {
		float(gamePoint.x) / game->getGemsField().getFieldSize().x * gameViewSize.x,
		gameViewSize.y - gemViewSize - float(gamePoint.y) / game->getGemsField().getFieldSize().y * gameViewSize.y
	};
}


Point WindowHandler::transformField(sf::Vector2i const& fieldPoint) {
	return {
		int(double(fieldPoint.x) / gameViewSize.x * game->getGemsField().getFieldSize().x),
		game->getGemsField().getFieldSize().y - 1 - int(double(fieldPoint.y) / gameViewSize.y * game->getGemsField().getFieldSize().y)
	};
}


bool WindowHandler::inGameView(sf::Vector2i const& mousePos) {
	return 0 <= mousePos.x && mousePos.x < gameViewSize.x &&
		0 <= mousePos.y && mousePos.y < gameViewSize.y;
}


void WindowHandler::render() {
	window.clear(sf::Color::Black);

	GemsField const& field = game->getGemsField();

	for (int y = 0; y < field.getFieldSize().y; y++) {
		for (int x = 0; x < field.getFieldSize().x; x++) {
			Gem const& gem = field.at(x, y);
			sf::CircleShape circle(gemViewSize / 2);

			if (gem.getFocus()) {
				circle.setOutlineThickness(gemViewSize / 100);
				circle.setOutlineColor(sf::Color::White);
			}
			circle.setFillColor(gemTypeToColor[gem.getType()]);
			circle.setPosition(transformGame({ x, y }));

			window.draw(circle);
		}
	}

	window.draw(fpsBar);

	window.display();
}


void WindowHandler::runMainLoop() {
	while (window.isOpen()) {
		sf::Event event;


		game->step();

		fpsBar.update();
		while (window.pollEvent(event)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (inGameView(mousePos)) {
					game->onClick(transformField(mousePos));
				}
				break;
			default:
				break;
			}
		}
		render();
	}
}

