#pragma once
#include <SFML/Graphics.hpp>

// Forward declare ScreenManager to avoid circular include
class ScreenManager;

// Singleton Game class: manages the main render window and the game loop
class Game 
{
public:
    // Get the singleton instance of Game
    static Game& getInstance();
    // Run the main game loop
    void run();
    // Signal the game to close (quit)
    void quit();
    // Access the SFML render window
    sf::RenderWindow& getWindow() {return window;}

    static constexpr unsigned int WIDTH = 1200;
    static constexpr unsigned int HEIGHT = 800;
    static constexpr unsigned int BASE_FONT_SIZE = 24;
private:
    Game();  // private constructor
    // Delete copy constructor and assignment (singleton non-copyable)
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    // Window and other members
    sf::RenderWindow window;
    
};
