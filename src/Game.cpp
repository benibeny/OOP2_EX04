#include "Game.h"
#include "ScreenManager.h"
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>

Game::Game() 
{
    // Create the main window (resizable)
    window.create(sf::VideoMode(WIDTH, HEIGHT), "Insaniquarium Game",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);
}

Game& Game::getInstance() 
{
    static Game instance;
    return instance;
}

void Game::run() 
{
    sf::Clock clock;
    // Main game loop
    while (window.isOpen()) 
    {
        sf::Time dt = clock.restart();
        // Process SFML window events
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            // Handle global close event
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
            // Forward event to the current active screen
            Screen* currentScreen = ScreenManager::getInstance().getCurrentScreen();
            if (currentScreen) 
            {
                currentScreen->handleEvent(event);
            }
            // If window was closed or a screen switch was triggered, break out of event loop
            if (!window.isOpen() || ScreenManager::getInstance().hasPendingScreen()) 
            {
                break;
            }
        }
        // If a screen change was requested, delete the old screen before continuing
        if (ScreenManager::getInstance().hasPendingScreen()) 
        {
            ScreenManager::getInstance().processScreenChange();
        }
        // If window was closed (e.g., Quit command), exit the loop
        if (!window.isOpen()) 
        {
            break;
        }
        // Update the current screen logic
        Screen* currentScreen = ScreenManager::getInstance().getCurrentScreen();
        if (currentScreen) 
        {
            currentScreen->update(dt.asSeconds());
        }
        // Render the current screen
        if (currentScreen) 
        {
            currentScreen->render(window);
        }
        window.display();
    }
    // Cleanup: delete remaining current screen (if any) after loop ends
    Screen* currScreen = ScreenManager::getInstance().getCurrentScreen();
    if (currScreen) 
    {
        delete currScreen;
        ScreenManager::getInstance().setCurrentScreen(nullptr);
    }
}

void Game::quit() 
{
    window.close();
}
