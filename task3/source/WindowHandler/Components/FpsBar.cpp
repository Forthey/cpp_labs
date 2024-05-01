#include "FpsBar.hpp"

#include <format>
#include <iostream>


FpsBar::FpsBar(sf::Vector2u const& windowSize)
{
	currentTime = timer.now();

	if (!bellFont.loadFromFile("fonts/BELL.ttf")) {
		return;
	}
	fpsText.setFont(bellFont);
	fpsText.setString("FPS: 0");
	fpsText.setPosition({ 0.93f * windowSize.x, 0.97f * windowSize.y });
}

void FpsBar::update()
{
	frames++;
	std::chrono::milliseconds deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(timer.now() - currentTime);
	if (deltaTime > std::chrono::milliseconds{1000}) {
		fps = 1000 * frames / deltaTime.count();
		frames = 0;
		currentTime = timer.now();

		fpsText.setString(std::format("FPS: {}", fps));
	}
}

void FpsBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(fpsText);
}

