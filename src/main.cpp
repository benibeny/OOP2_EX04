#include "Game.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"

int main() 
{
    // Initialize the Game and ScreenManager singletons
    Game& game = Game::getInstance();
    ScreenManager& screenManager = ScreenManager::getInstance();
    // Start the game at the main menu screen
    screenManager.switchScreen(new MenuScreen());
    // Enter the main game loop
    game.run();
    return 0;
}
