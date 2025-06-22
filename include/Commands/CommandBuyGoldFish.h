#pragma once

#include "Command.h"
#include <iostream>

class CommandBuyGoldFish : public Command
{
	void execute() override { std::cout << "hello"; }
};