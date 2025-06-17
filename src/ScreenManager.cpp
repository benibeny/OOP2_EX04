#include "ScreenManager.h"
#include "Screens/Screen.h"

ScreenManager& ScreenManager::getInstance() 
{
    static ScreenManager instance;
    return instance;
}

void ScreenManager::switchScreen(Screen* newScreen) 
{
    // Store the current screen for deletion (if it exists)
    if (currentScreen != nullptr) 
    {
        oldScreen = currentScreen;
    }
    // Switch to the new screen immediately
    currentScreen = newScreen;
}

void ScreenManager::processScreenChange() 
{
    if (oldScreen) 
    {
        delete oldScreen;
        oldScreen = nullptr;
    }
}
