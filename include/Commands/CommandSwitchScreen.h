#pragma once

#include "Commands/Command.h"
#include "Screens/HelpScreen.h"
#include "Managers/ScreenManager.h"

class CommandSwitchScreen : public Command
{
public:
	CommandSwitchScreen(ScreenType levelType);

	void execute() override;
private:
	ScreenType m_levelType;
};

