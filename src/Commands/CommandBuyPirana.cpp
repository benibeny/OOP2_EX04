#include "Commands/CommandBuyPirana.h"


void CommandBuyPirana::execute()
{
	EventManager::getInstance().notifyBuyAnimal(std::make_unique<Pirana>(sf::Vector2f(500.0f, 500.0f)));
}