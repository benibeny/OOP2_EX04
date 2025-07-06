#include "Commands/CommandSwitchScreen.h"


CommandSwitchScreen::CommandSwitchScreen(ScreenType levelType)
	:m_levelType(levelType)	
{}


void CommandSwitchScreen::execute()
{
	ScreenManager::getInstance().switchScreen(m_levelType);
}