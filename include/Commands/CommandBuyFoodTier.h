#pragma once

#include "Command.h"
#include "Managers/EventManager.h"
#include <iostream>

class CommandBuyFoodTier : public Command
{
	void execute() override;
};