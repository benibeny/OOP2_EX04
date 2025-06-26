#pragma once
// Forward declare Screen class
#include <SFML/Graphics/RenderWindow.hpp> // Ensure this include is added to resolve sf::RenderWindow type
#include <memory>

class Screen;
class MenuScreen;
class HelpScreen;class GameScreen;


enum class ScreenType
{
    MainMenu,
    GameScreen,
	HelpScreen,
};

// Singleton ScreenManager: handles screen transitions and current screen management
class ScreenManager 
{
public:
    

    static ScreenManager& getInstance();
    // Switch to a new screen. The old screen is scheduled to be deleted.
    void switchScreen(ScreenType screen);

    
  

	void updateAndRender(float deltaTime, sf::RenderWindow& window);
	void handleEvents(const sf::Event& event);
   
 
private:
	std::unique_ptr<MenuScreen> m_mainMenuScreen;
	std::unique_ptr<GameScreen> m_gameScreen;
	std::unique_ptr<HelpScreen> m_helpScreen;

	ScreenType m_screenType;



    ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
    
};
