#include "ScreenManager.h"
#include "Screens/Screen.h"
#include "Screens/MenuScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/HelpScreen.h"
#include "Screens/ChooseLevelScreen.h"


ScreenManager::ScreenManager() :m_screenType(ScreenType::MainMenu)
{
	

	m_screens[ScreenType::Level1] = std::make_unique<GameScreen>(1);
	m_screens[ScreenType::Level2] = std::make_unique<GameScreen>(2);
	m_screens[ScreenType::Level3] = std::make_unique<GameScreen>(3);
	m_screens[ScreenType::Level4] = std::make_unique<GameScreen>(4);
	m_screens[ScreenType::ChooseLevelScreen] = std::make_unique<ChooseLevelScreen>();
	m_screens[ScreenType::HelpScreen] = std::make_unique<HelpScreen>();
	m_screens[ScreenType::MainMenu] = std::make_unique<MenuScreen>();
}

ScreenManager& ScreenManager::getInstance() 
{
    static ScreenManager instance;
    return instance;
}

void ScreenManager::switchScreen(ScreenType screen)
{
	m_screens[m_screenType]->setActive(false);
	if (m_screens.contains(screen))
	{
		m_screenType = screen;
		m_screens[m_screenType]->setActive(true);
	}
}
	

void ScreenManager::updateAndRender(float deltaTime, sf::RenderWindow& window)
{
	if (m_screens.contains(m_screenType))
	{
		m_screens[m_screenType]->render(window);
		m_screens[m_screenType]->update(deltaTime);
		
	}
}

void ScreenManager::handleEvents(const sf::Event& event)
{
	if (m_screens.contains(m_screenType))
	{
		m_screens[m_screenType]->handleEvent(event);
	}
}

void ScreenManager::reset(ScreenType screen)
{
	if (m_screens.contains(m_screenType))
	{
		m_screens[m_screenType]->reset();
	}
}

void ScreenManager::reset()
{
	reset(m_screenType);
}


