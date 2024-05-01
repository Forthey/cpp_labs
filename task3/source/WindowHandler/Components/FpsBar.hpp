#pragma once
#include <chrono>

#include <SFML/Graphics.hpp>

class FpsBar : public sf::Drawable {
	float fps = 0;
	unsigned frames = 0;
	std::chrono::high_resolution_clock timer;
	std::chrono::steady_clock::time_point currentTime;

	sf::Text fpsText;
	sf::Font bellFont;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	FpsBar(sf::Vector2u const& windowSize);
	void update();
};

