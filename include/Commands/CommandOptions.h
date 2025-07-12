#pragma once

#include "Command.h"
#include "Managers/EventManager.h"


class CommandOptions : public Command
{
	void execute() override;
};