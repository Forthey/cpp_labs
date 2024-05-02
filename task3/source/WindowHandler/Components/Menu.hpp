#pragma once
#include <SFML/Graphics.hpp>


enum class MenuClickResult {
	RESTART = 0,
	END,
	NONE
};


class Menu : public sf::Drawable
{
	sf::Vector2f const menuFill = { 0.2f, 0.4f };
	sf::RectangleShape menuRect;

	sf::Font font;
	float const spacing = 10.0f;
	std::vector<std::string> const buttonStrings = {
		"restart",
		"end"
	};
	std::vector<sf::Text> buttons;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool buttonClicked(sf::Vector2i const& mousePos, sf::Text const& button);
public:
	Menu(sf::Vector2u const& windowSize);

	bool inView(sf::Vector2i const& mousePos);
	MenuClickResult onClick(sf::Vector2i const& mousePos);
};

