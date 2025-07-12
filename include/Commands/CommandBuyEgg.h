#pragma once

#include "Command.h"
#include "Managers/EventManager.h"
#include "Managers/ScreenManager.h"
#include <iostream>

class CommandBuyEgg : public Command
{
public:
	CommandBuyEgg(int nextLevel);

	void execute() override;
private:	
	int m_nextLevel;
};