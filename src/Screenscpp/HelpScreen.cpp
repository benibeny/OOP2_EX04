#include "Screens/HelpScreen.h"
#include "Game.h"
#include "ScreenManager.h"
#include "Screens/MenuScreen.h"
#include <iostream>
#include "Commands/SwitchBackgroundCommand.h"

HelpScreen::HelpScreen()
{
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cerr << "Failed to load font for HelpScreen.\n";
    }

    if (!backgroundTexture.loadFromFile("talkshow.png")) {
        std::cerr << "Failed to load help background image.\n";
    }

    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
    backgroundSprite.setScale(
        winSize.x / (float)backgroundTexture.getSize().x,
        winSize.y / (float)backgroundTexture.getSize().y
    );

    unsigned int fontSize = static_cast<unsigned int>(winSize.y * 0.03f);
    float lineSpacing = fontSize + 10.f;


    // Footer text
    footerText.setFont(font);
    footerText.setString("Press ESC to return to the main menu");
    footerText.setCharacterSize(static_cast<unsigned int>(fontSize * 0.9f));
    footerText.setFillColor(sf::Color::Black);
    footerText.setOutlineColor(sf::Color::White);
    footerText.setOutlineThickness(2.f);

    sf::FloatRect footerBounds = footerText.getLocalBounds();
    //footerText.setOrigin(footerBounds.width / 2.f, 0.f);
    footerText.setPosition(15.f, 50.f);



    auto command = std::make_unique<SwitchBackgroundCommand>(this);
    switchBackgroundButton = std::make_unique<Button>("next", font, std::move(command));
    switchBackgroundButton->setRelativePosition(0.5f, 0.95f);
    switchBackgroundButton->resize(winSize);

}


void HelpScreen::handleEvent(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Escape) 
    {
        ScreenManager::getInstance().switchScreen(ScreenType::MainMenu);
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
    {
        float x = static_cast<float>(event.mouseButton.x);
        float y = static_cast<float>(event.mouseButton.y);
        if (switchBackgroundButton && switchBackgroundButton->contains(x, y)) {
            switchBackgroundButton->onClick();
        }
    }
}

void HelpScreen::update(float)
{
    if (switchBackgroundButton) 
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(Game::getInstance().getWindow());
        bool isHovering = switchBackgroundButton->contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        switchBackgroundButton->setHover(isHovering);
        sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
        switchBackgroundButton->resize(winSize);
    }
}


void HelpScreen::render(sf::RenderWindow& window) {
    if (backgroundTexture.getSize().x == 0 || font.getInfo().family.empty())
        return;

    window.draw(backgroundSprite);

    window.draw(footerText);

    if (switchBackgroundButton)
        switchBackgroundButton->draw(window);

}

void HelpScreen::toggleBackground() {
    // Move to next background index
    m_backgroundIndex = (m_backgroundIndex + 1) % 4; // assuming 4 backgrounds

    std::string fileName;
    switch (m_backgroundIndex) {
    case 0: fileName = "talkshow.png"; break;
    case 1: fileName = "tips0.png"; break;
    case 2: fileName = "tips1.png"; break;
    case 3: fileName = "tips2.png"; break;
    }

    if (!backgroundTexture.loadFromFile(fileName)) {
        std::cerr << "Failed to load background image: " << fileName << "\n";
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u winSize = Game::getInstance().getWindow().getSize();
    backgroundSprite.setScale(
        winSize.x / static_cast<float>(backgroundTexture.getSize().x),
        winSize.y / static_cast<float>(backgroundTexture.getSize().y)
    );
}


void HelpScreen::setActive(bool active)
{
    m_isActive = active;
}

void HelpScreen::reset() {}