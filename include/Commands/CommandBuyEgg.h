#pragma once

#include "Command.h"
#include "EventManager.h"
#include <iostream>

class CommandBuyEgg : public Command
{
	void execute() override;
};