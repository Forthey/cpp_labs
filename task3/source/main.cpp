#include <iostream>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Game/Game.hpp"


class WindowEventHandler {
	sf::RenderWindow& window;
	std::unique_ptr<Game> game;
	sf::Vector2f gameViewSize;
	float gemViewSize;
	float const gameViewFill = 0.9f;
	std::unordered_map<GemType, sf::Color> gemTypeToColor = {
		{GemType::BLUE, sf::Color::Blue},
		{GemType::GREEN, sf::Color::Green},
		{GemType::RED, sf::Color::Red},
		{GemType::YELLOW, sf::Color::Yellow},
	};
public:
	explicit WindowEventHandler(sf::RenderWindow& window) : window(window) {
		game = std::make_unique<Game>(3, 3);

		gemViewSize = gameViewFill * window.getSize().y / game->getGemsField().getFieldSize().y;

		gameViewSize = { 
			gemViewSize * game->getGemsField().getFieldSize().x,
			gemViewSize * game->getGemsField().getFieldSize().y
		};
	}

	sf::Vector2f transformGame(Point const& gamePoint) {
		return {
			float(gamePoint.x) / game->getGemsField().getFieldSize().x * gameViewSize.x,
			float(gamePoint.y) / game->getGemsField().getFieldSize().y * gameViewSize.y
		};
	}

	Point transformField(sf::Vector2i const& fieldPoint) {
		return {
			int(double(fieldPoint.x) / gameViewSize.x * game->getGemsField().getFieldSize().x),
			int(double(fieldPoint.y) / gameViewSize.y * game->getGemsField().getFieldSize().y)
		};
	}

	void render() {
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
				circle.setPosition(transformGame({x, y}));

				window.draw(circle);
			}
		}
		
		window.display();
	}

	bool inGameView(sf::Vector2i const& mousePos) {
		return 0 <= mousePos.x && mousePos.x < gameViewSize.x &&
			0 <= mousePos.y && mousePos.y < gameViewSize.y;
	}

	void runMainLoop() {
		while (window.isOpen()) {
			sf::Event event;

			if (!window.hasFocus()) {
				continue;
			}

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
};


int main() {
	sf::RenderWindow rw(
		sf::VideoMode(
			2 * sf::VideoMode::getDesktopMode().width / 3,
			2 * sf::VideoMode::getDesktopMode().height / 3
		),
		"GEMS"
		// sf::Style::Fullscreen
	);

	WindowEventHandler windowEventHandler(rw);

	windowEventHandler.runMainLoop();
	return 0;
}