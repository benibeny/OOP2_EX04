#pragma once

#include "Commands/Command.h"
#include "Screens/HelpScreen.h"
#include "Managers/ScreenManager.h"

class StartLevelCommand : public Command
{
public:
    StartLevelCommand(ScreenType levelType);
	StartLevelCommand(int level);

	void execute() override;
private:
	ScreenType m_levelType;
};

