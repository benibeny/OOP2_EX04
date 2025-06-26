#include "ScreenManager.h"
#include "Screens/Screen.h"
#include "Screens/MenuScreen.h"
#include "Screens/GameScreen.h"
#include "Screens/HelpScreen.h"


ScreenManager::ScreenManager() :m_screenType(ScreenType::MainMenu)
{
	m_mainMenuScreen = std::make_unique<MenuScreen>();
    m_gameScreen = std::make_unique<GameScreen>();
	m_helpScreen = std::make_unique<HelpScreen>();
   
}

ScreenManager& ScreenManager::getInstance() 
{
    static ScreenManager instance;
    return instance;
}

void ScreenManager::switchScreen(ScreenType screen) 
{
	m_screenType = screen;
}

void ScreenManager::updateAndRender(float deltaTime, sf::RenderWindow& window)
{
	switch (m_screenType)
	{
	case ScreenType::MainMenu:
		m_mainMenuScreen->update(deltaTime);
		m_mainMenuScreen->render(window);
		break;

	case ScreenType::GameScreen:
		m_gameScreen->update(deltaTime);
		m_gameScreen->render(window);
		break;

	case ScreenType::HelpScreen:
		m_helpScreen->update(deltaTime);
		m_helpScreen->render(window);
		break;

	default:
		break;
	}
}

void ScreenManager::handleEvents(const sf::Event& event)
{
	switch (m_screenType)
	{
	case ScreenType::MainMenu:
		m_mainMenuScreen->handleEvent(event);
		break;
	case ScreenType::GameScreen:
		m_gameScreen->handleEvent(event);
		break;
	case ScreenType::HelpScreen:
		m_helpScreen->handleEvent(event);
		break;
	default:
		break;
	}
}


