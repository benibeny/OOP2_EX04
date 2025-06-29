#include "Commands/StartLevelCommand.h"

StartLevelCommand::StartLevelCommand(ScreenType levelType)
	:m_levelType(levelType)
{}

StartLevelCommand::StartLevelCommand(int level)
{
	switch (level)
	{
	case 1:// Level 1
		m_levelType = ScreenType::Level1;
		break;
	case 2:// Level 2
		m_levelType = ScreenType::Level2;
		break;
	case 3:// Level 3
		m_levelType = ScreenType::Level3;
		break;
	case 4:// Level 4
		m_levelType = ScreenType::Level4;
		break;

	default:
		m_levelType = ScreenType::Level1;
		break;
	}
}


void StartLevelCommand::execute()
{
	ScreenManager::getInstance().switchScreen(m_levelType);
}