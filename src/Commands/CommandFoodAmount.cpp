#include "Commands/CommandBuyFoodAmount.h"

void CommandBuyFoodAmount::execute()
{
	EventManager::getInstance().notifyFoodAmount();
}