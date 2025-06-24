#include "Commands/CommandBuyFoodTier.h"


void CommandBuyFoodTier::execute()
{
	EventManager::getInstance().notifyFoodTier();
}