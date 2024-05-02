#include "GameView.hpp"


GameView::GameView(sf::Vector2u const& windowSize)
{
	game = std::make_unique<Game>(10, 10);

	gemViewSize = gameViewFill * windowSize.y / game->getGemsField().getFieldSize().y;

	gameViewSize = {
		gemViewSize * game->getGemsField().getFieldSize().x,
		gemViewSize * game->getGemsField().getFieldSize().y
	};
}


sf::Vector2f GameView::transformGame(Point const& gamePoint) const {
	return {
		float(gamePoint.x) / game->getGemsField().getFieldSize().x * gameViewSize.x,
		gameViewSize.y - gemViewSize - float(gamePoint.y) / game->getGemsField().getFieldSize().y * gameViewSize.y
	};
}


Point GameView::transformField(sf::Vector2i const& fieldPoint) const {
	return {
		int(double(fieldPoint.x) / gameViewSize.x * game->getGemsField().getFieldSize().x),
		game->getGemsField().getFieldSize().y - 1 - int(double(fieldPoint.y) / gameViewSize.y * game->getGemsField().getFieldSize().y)
	};
}


bool GameView::inView(sf::Vector2i const& mousePos) const {
	return 0 <= mousePos.x && mousePos.x < gameViewSize.x &&
		0 <= mousePos.y && mousePos.y < gameViewSize.y;
}


void GameView::onClick(sf::Vector2i const& mousePos)
{
	game->onClick(transformField(mousePos));
}


void GameView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	GemsField const& field = game->getGemsField();

	for (int y = 0; y < field.getFieldSize().y; y++) {
		for (int x = 0; x < field.getFieldSize().x; x++) {
			Gem const& gem = field.at(x, y);

			if (gem.getType() == GemType::NONE) {
				continue;
			}

			sf::CircleShape circle(gemViewSize / 2);
			sf::Color gemColor = gemTypeToColor.at(gem.getType());

			if (gem.getFocus()) {
				sf::Color focusedColor(
					sf::Uint8(std::min(255, gemColor.r + 150)),
					sf::Uint8(std::min(255, gemColor.g + 150)),
					sf::Uint8(std::min(255, gemColor.b + 150))
				);

				circle.setFillColor(focusedColor);
			}
			else {
				circle.setFillColor(gemTypeToColor.at(gem.getType()));
			}
			circle.setPosition(transformGame({ x, y }));

			target.draw(circle);
		}
	}
}


void GameView::update()
{
	game->step();
}
