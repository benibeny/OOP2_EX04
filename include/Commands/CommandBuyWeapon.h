#pragma once

#include "Command.h"
#include <iostream>

class CommandBuyWeapon : public Command
{
	void execute() override { std::cout << "hello"; }
};