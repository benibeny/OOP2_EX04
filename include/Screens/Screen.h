#pragma once
#include <SFML/Graphics.hpp>

// Abstract Screen class: defines interface for different game screens
class Screen {
public:
    virtual ~Screen() {}
    // Handle input events relevant to this screen
    virtual void handleEvent(const sf::Event& event) = 0;
    // Update the screen state (deltaTime is elapsed time in seconds)
    virtual void update(float deltaTime) = 0;
    // Render the screen contents onto the given window
    virtual void render(sf::RenderWindow& window) = 0;
};
