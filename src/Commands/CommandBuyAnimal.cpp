#include "Commands/CommandBuyGoldFish.h"
#include "GameObjectFactory.h"


void CommandBuyGoldFish::execute()
{
	EventManager::getInstance().notifyBuyAnimal(GameObjectFactory::getInstance().create("GoldFish", { 500.0f, 500.0f }));
}