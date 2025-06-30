#include "Game.h"
#include "ScreenManager.h"
#include "Screens/Screen.h"
#include <SFML/Graphics.hpp>
#include "MusicManager.h" 

#include "SoundManager.h"

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
    MusicManager::getInstance().loadAndPlay("menu", "musicbackround.ogg", true); 
    SoundManager::getInstance().initialize(); //add

    ScreenManager& screen = ScreenManager::getInstance();
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
			screen.handleEvents(event);
        }
        
        // If window was closed (e.g., Quit command), exit the loop
        if (!window.isOpen()) 
        {
            break;
        }
        screen.updateAndRender(dt.asSeconds(),window);
        
        window.display();
    }
    
}

void Game::quit() 
{
    window.close();
}
