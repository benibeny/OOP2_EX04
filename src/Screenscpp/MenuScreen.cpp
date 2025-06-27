#include <iostream>
#include <memory>

#include "Commands/Command.h"
#include "Commands/StartAdventureCommand.h"
#include "Commands/ShowHelpCommand.h"
#include "Commands/QuitGameCommand.h"

#include "Screens/MenuScreen.h"
#include "ScreenManager.h"
#include "Game.h"
#include "ResourceManager.h"

MenuScreen::MenuScreen() 
{
    sf::RenderWindow& window = Game::getInstance().getWindow();
    sf::Vector2u size = window.getSize();
    window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(size.x), static_cast<float>(size.y))));

    


    // Initialize background texture and sprite
    sf::Vector2u winSize = window.getSize();
    if (!backgroundTexture.loadFromFile("titlescreen.jpg")) 
    {
        std::cerr << "Failed to load background image!\n";
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(winSize.x) / backgroundTexture.getSize().x,
        static_cast<float>(winSize.y) / backgroundTexture.getSize().y);

	sf::Font& font = ResourceManager::getInstance().getGameFont();
    
    // Create menu buttons with their respective commands
    buttons.emplace_back("Start Adventure", font, std::make_unique<StartAdventureCommand>());
    buttons.emplace_back("Help", font, std::make_unique<ShowHelpCommand>());
    buttons.emplace_back("Quit Game", font, std::make_unique<QuitGameCommand>());

    // Set normalized positions for each button (centered horizontally, spaced vertically)
    float startY = 0.5f;
    float stepY = 0.2f;

    for (size_t i = 0; i < buttons.size(); ++i) 
    {
        float posY = startY + i * stepY;
        buttons[i].setRelativePosition(0.5f, posY);
        buttons[i].setBaseCharacterSize(Game::BASE_FONT_SIZE);
        buttons[i].resize(winSize);
    }

}

void MenuScreen::handleEvent(const sf::Event& event) 
{
    if (event.type == sf::Event::Resized) 
    {
        // Adjust SFML view to match new window size
        sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
        Game::getInstance().getWindow().setView(sf::View(visibleArea));

        // Adjust background size
        backgroundSprite.setScale(
            static_cast<float>(event.size.width) / backgroundTexture.getSize().x,
            static_cast<float>(event.size.height) / backgroundTexture.getSize().y);

        // Adjust button layout
        sf::Vector2u newSize(event.size.width, event.size.height);
        for (auto& btn : buttons) {
            btn.resize(newSize);
        }
    }
    else if (event.type == sf::Event::MouseMoved) 
    {
        // Update hover state for each button based on mouse position
        float mouseX = static_cast<float>(event.mouseMove.x);
        float mouseY = static_cast<float>(event.mouseMove.y);
        for (auto& btn : buttons) {
            bool hovering = btn.contains(mouseX, mouseY);
            btn.setHover(hovering);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed) 
    {
        if (event.mouseButton.button == sf::Mouse::Left) 
        {
            float mouseX = static_cast<float>(event.mouseButton.x);
            float mouseY = static_cast<float>(event.mouseButton.y);
            // Check which button was clicked and execute its action
            for (auto& btn : buttons) 
            {
                if (btn.contains(mouseX, mouseY)) 
                {
                    btn.onClick();
                    break;  // Only trigger one button action on click
                }
            }
        }
    }
}

void MenuScreen::update(float /*deltaTime*/) 
{
    // Static menu: no per-frame updates needed (could add animations here)
}

void MenuScreen::render(sf::RenderWindow& window) 
{
    // Draw background and then all buttons
    window.draw(backgroundSprite);
    for (auto& btn : buttons) {
        btn.draw(window);
    }
}
