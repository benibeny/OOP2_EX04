#include "Game.h"
#include "Managers/ScreenManager.h"
#include "Screens/MenuScreen.h"

int main() 
{
    // Initialize the Game and ScreenManager singletons
    Game& game = Game::getInstance();
    ScreenManager& screenManager = ScreenManager::getInstance();
    // Start the game at the main menu screen
    screenManager.switchScreen(ScreenType::MainMenu);
    // Enter the main game loop
    game.run();
    return 0;
}
