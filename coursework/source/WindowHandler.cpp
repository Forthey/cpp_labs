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
			parseEvent(event);
		}

		float const mousePosX = static_cast<float>(sf::Mouse::getPosition(*window).x);
		arkanoid->update(mousePosX);

		window->draw(*arkanoid);
		window->display();
	}
}


void WindowHandler::parseEvent(sf::Event const& event) {
	switch (event.type)
	{
	case sf::Event::Closed:
		window->close();
		break;
	case sf::Event::KeyPressed:
		parsePressedButtons(event.key.code);
		break;
	case sf::Event::LostFocus:
		arkanoid->pause();
		break;
	case sf::Event::GainedFocus:
		arkanoid->start();
		break;
	default:
		break;
	}
}

void WindowHandler::parsePressedButtons(sf::Keyboard::Key const& key) {
	switch (key) {
	case sf::Keyboard::R:
		arkanoid = std::make_unique<Arkanoid>(window->getSize());
		break;
	case sf::Keyboard::Space:
		arkanoid->switchState();
		break;
	}
}
