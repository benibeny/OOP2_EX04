#pragma once

#include "Command.h"
#include "EventManager.h"
#include <iostream>

class CommandBuyFoodTier : public Command
{
	void execute() override;
};