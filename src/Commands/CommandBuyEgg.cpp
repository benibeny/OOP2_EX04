#include "Commands/CommandBuyEgg.h"


CommandBuyEgg::CommandBuyEgg(int nextLevel)
	: m_nextLevel(nextLevel)
{}

void CommandBuyEgg::execute()
{
	ScreenManager::getInstance().reset();
	EventManager::getInstance().notifyNextLevel(m_nextLevel);
	ScreenManager::getInstance().switchScreen(ScreenType::ChooseLevelScreen);
}