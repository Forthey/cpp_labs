#include "WindowHandler.hpp"


WindowHandler::WindowHandler(sf::RenderWindow& window) : 
	window(window), 
	fpsBar(window.getSize()), 
	game(window.getSize()), 
	menu(window.getSize()) {
}


void WindowHandler::render() {
	window.clear(sf::Color::Black);

	
	window.draw(game);
	window.draw(fpsBar);
	window.draw(menu);

	window.display();
}


void WindowHandler::runMainLoop() {
	while (window.isOpen()) {
		sf::Event event;

		game.update();
		fpsBar.update();

		while (window.pollEvent(event)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (game.inView(mousePos)) {
					game.onClick(mousePos);
				}
				else if (menu.inView(mousePos)) {
					switch (menu.onClick(mousePos)) {
					case MenuClickResult::RESTART:
						game.restart();
						break;
					case MenuClickResult::END:
						game.end();
						break;
					}
				}
				break;
			default:
				break;
			}
		}
		render();
	}
}

