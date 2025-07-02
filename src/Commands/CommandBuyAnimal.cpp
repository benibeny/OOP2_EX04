#include "Commands/CommandBuyGoldFish.h"


void CommandBuyGoldFish::execute()
{

	sf::Vector2u windowSize = Game::getInstance().getWindow().getSize();
	EventManager::getInstance().notifyBuyAnimal(std::make_unique<GoldFish>(sf::Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f)));
}