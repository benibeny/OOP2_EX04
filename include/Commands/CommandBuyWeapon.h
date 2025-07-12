#pragma once

#include "Command.h"
#include "Managers/EventManager.h"
#include <iostream>

class CommandBuyWeapon : public Command
{
	void execute() override;
};