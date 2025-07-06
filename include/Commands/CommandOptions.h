#pragma once

#include "Command.h"
#include "EventManager.h"


class CommandOptions : public Command
{
	void execute() override;
};