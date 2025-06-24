#pragma once

#include "Command.h"
#include "EventManager.h"
#include <iostream>

class CommandBuyFoodAmount : public Command
{
	void execute() override;
};