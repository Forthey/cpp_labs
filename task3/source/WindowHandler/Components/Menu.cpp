#include "Menu.hpp"


Menu::Menu(sf::Vector2u const& windowSize) : menuRect({menuFill.x * windowSize.x, menuFill.y * windowSize.y}) {

	if (!font.loadFromFile("fonts/BELL.ttf")) {
		return;
	}
	menuRect.setPosition((1.0f - menuFill.x) * windowSize.x, 0);
	menuRect.setFillColor(sf::Color::Black);
	menuRect.setOutlineThickness(1);
	menuRect.setOutlineColor(sf::Color::White);

	for (int i = 0; i < buttonStrings.size(); i++) {
		sf::Text button;
		button.setFont(font);
		button.setString(buttonStrings[i]);
		button.setCharacterSize(windowSize.x / 40);
		button.setPosition({
			menuRect.getPosition().x + (menuRect.getSize().x - button.getGlobalBounds().width) / 2,
			menuRect.getPosition().y + (i + 1) * spacing + i * button.getCharacterSize()
		});
		buttons.push_back(button);
	}
}


bool Menu::inView(sf::Vector2i const& mousePos) {
	std::pair<float, float> menuX = { menuRect.getPosition().x, menuRect.getPosition().x + menuRect.getSize().x };
	std::pair<float, float> menuY = { menuRect.getPosition().y, menuRect.getPosition().y + menuRect.getSize().y };
	return menuX.first <= mousePos.x && mousePos.x <= menuX.second 
		&& menuY.first <= mousePos.y && mousePos.y <= menuY.second;
}


MenuClickResult Menu::onClick(sf::Vector2i const& mousePos) {
	for (int i = 0; i < buttons.size(); i++) {
		if (buttonClicked(mousePos, buttons[i])) {
			return MenuClickResult(i);
		}
	}

	return MenuClickResult::NONE;
}


bool Menu::buttonClicked(sf::Vector2i const& mousePos, sf::Text const& button) {
	std::pair<float, float> posX = { button.getPosition().x, button.getPosition().x + button.getGlobalBounds().width };
	std::pair<float, float> posY = { button.getPosition().y, button.getPosition().y + button.getCharacterSize()};
	return posX.first <= mousePos.x && mousePos.x <= posX.second
		&& posY.first <= mousePos.y && mousePos.y <= posY.second;
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(menuRect);
	for (auto const& button : buttons) {
		target.draw(button);
	}
}
