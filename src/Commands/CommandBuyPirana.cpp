#include "Commands/CommandBuyPirana.h"
#include "GameObjectFactory.h"


void CommandBuyPirana::execute()
{
	EventManager::getInstance().notifyBuyAnimal(GameObjectFactory::getInstance().create("Pirana", { 500.0f, 500.0f }));
}