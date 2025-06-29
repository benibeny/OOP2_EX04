#pragma once
// Forward declare Screen class
#include <SFML/Graphics/RenderWindow.hpp> // Ensure this include is added to resolve sf::RenderWindow type
#include <memory>
#include <unordered_map>



class Screen;
class MenuScreen;
class HelpScreen;
class GameScreen;
class ChooseLevelScreen;


enum class ScreenType
{
    MainMenu,
	HelpScreen,
    ChooseLevelScreen,
    Level1,
    Level2,
    Level3,
    Level4,

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
    std::unordered_map <ScreenType, std::unique_ptr<Screen>> m_screens;

	ScreenType m_screenType;

    

    ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
    
};
