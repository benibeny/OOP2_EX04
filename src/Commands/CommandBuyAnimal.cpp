#include "Commands/CommandBuyGoldFish.h"


void CommandBuyGoldFish::execute()
{
	EventManager::getInstance().notifyBuyAnimal(std::make_unique<GoldFish>(sf::Vector2f(500.0f, 500.0f)));
}