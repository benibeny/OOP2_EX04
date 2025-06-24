#pragma once

#include "Command.h"
#include <iostream>

class CommandBuyPirana : public Command
{
	void execute() override { std::cout << "hello"; }
};