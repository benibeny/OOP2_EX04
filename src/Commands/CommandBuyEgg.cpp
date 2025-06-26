#include "Commands/CommandBuyEgg.h"


void CommandBuyEgg::execute()
{
	EventManager::getInstance().notifyNextLevel();
}