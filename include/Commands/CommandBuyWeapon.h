#pragma once

#include "Command.h"
#include "EventManager.h"
#include <iostream>

class CommandBuyWeapon : public Command
{
	void execute() override;
};