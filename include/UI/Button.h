#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Commands/Command.h"
#include "Managers/ResourceManager.h"    

// Button class: represents a clickable text button that executes a Command
class Button 
{
public:
    Button(const std::string& textString, sf::Font& m_font, std::unique_ptr<Command> cmd);
    // Non-copyable (contains unique_ptr)
    Button(const Button&) = delete;
    Button& operator=(const Button&) = delete;

    // Movable to allow storage in containers
    Button(Button&&) noexcept = default;
    Button& operator=(Button&&) noexcept = default;

    // Check if a given point (e.g., mouse coordinates) lies within the button
    bool contains(float x, float y) const;

    // Set hover state (enlarge or reset the button appearance)
    void setHover(bool hover);

    // Trigger the button's action (execute its command)
    void onClick();

    // Recompute the button's size and position based on a new window size
    void resize(const sf::Vector2u& windowSize);

    // Set the relative (normalized) position of the button's center (0.0 to 1.0)
    void setRelativePosition(float relX, float relY) { relativeX = relX; relativeY = relY; }
    // Set the base character size for the button text (at reference window size)
    void setBaseCharacterSize(unsigned int size) { baseCharSize = size; }
    // Draw the button (its text) to the window
    void draw(sf::RenderWindow& window) const;
 
    void setColor(const sf::Color& color);
private:
    sf::Text text;
    std::unique_ptr<Command> command;
    bool isHovered;
    // Relative normalized position of the button's center (as fraction of window width/height)
    float relativeX;
    float relativeY;
    // Base text size for reference resolution (e.g., 800x600)
    unsigned int baseCharSize;


    sf::RectangleShape background;
    sf::Color normalColor = sf::Color(50, 50, 150);   // background color
    sf::Color hoverColor = sf::Color(70, 70, 200);    // hover color
    float outlineThickness = 2.f;
};
