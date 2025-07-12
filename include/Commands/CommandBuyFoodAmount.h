#pragma once

#include "Command.h"
#include "Managers/EventManager.h"
#include <iostream>

class CommandBuyFoodAmount : public Command
{
	void execute() override;
};