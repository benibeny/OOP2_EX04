#pragma once

#include "Command.h"
#include "EventManager.h"
#include "ScreenManager.h"
#include <iostream>

class CommandBuyEgg : public Command
{
public:
	CommandBuyEgg(int nextLevel);

	void execute() override;
private:	
	int m_nextLevel;
};