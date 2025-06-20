#pragma once

#include "Commands/CommandButton/CommandShopBar.h"


class CommandOptions : public CommandShopBar
{
	bool execute() override { return true; }
};