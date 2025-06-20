#pragma once

#include "Commands/CommandButton/CommandShopBar.h"


class CommandBuyGoldFish : public CommandShopBar
{
	bool execute() override { return true; }
};