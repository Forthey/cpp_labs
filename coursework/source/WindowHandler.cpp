#include "WindowHandler.hpp"

WindowHandler::WindowHandler(sf::Vector2f const& screenFill) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window = std::make_unique<sf::RenderWindow>(
		sf::VideoMode(
			static_cast<unsigned int>(sf::VideoMode::getDesktopMode().width * screenFill.x),
			static_cast<unsigned int>(sf::VideoMode::getDesktopMode().height * screenFill.y)
		),
		"Arkanoid",
		sf::Style::Default,
		settings
	);
	window->setMouseCursorVisible(false);

	arkanoid = std::make_unique<Arkanoid>(window->getSize());
}


void WindowHandler::runMainLoop()
{
	while (window->isOpen()) {
		sf::Event event;

		window->clear(sf::Color::Black);

		while (window->pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::Closed:
				window->close();
				break;
			default:
				break;
			}
		}

		float const mousePosX = static_cast<float>(sf::Mouse::getPosition(*window).x);
		arkanoid->update(mousePosX);

		window->draw(*arkanoid);
		window->display();
	}
}
