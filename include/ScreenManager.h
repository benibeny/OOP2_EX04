#pragma once
// Forward declare Screen class
class Screen;

// Singleton ScreenManager: handles screen transitions and current screen management
class ScreenManager 
{
public:
    static ScreenManager& getInstance();
    // Switch to a new screen. The old screen is scheduled to be deleted.
    void switchScreen(Screen* newScreen);
    // Get the current active screen
    Screen* getCurrentScreen() const { return currentScreen; }
    // Check if a screen switch is pending deletion
    bool hasPendingScreen() const { return (oldScreen != nullptr); }
    // Complete a pending screen switch by deleting the old screen
    void processScreenChange();
    // (For cleanup) Set the current screen pointer
    void setCurrentScreen(Screen* screen) { currentScreen = screen; }
private:
    ScreenManager() : currentScreen(nullptr), oldScreen(nullptr) {}
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator=(const ScreenManager&) = delete;
    Screen* currentScreen;
    Screen* oldScreen;  // stores the previous screen to delete after switching
};
