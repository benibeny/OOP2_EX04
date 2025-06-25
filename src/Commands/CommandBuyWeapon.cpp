#include "Commands/CommandBuyWeapon.h"

void CommandBuyWeapon::execute()
{
	EventManager::getInstance().notifyBuyWeapon();
}