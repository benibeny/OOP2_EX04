#include "Button.h"
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

Button::Button(const std::string& textString, sf::Font& font, std::unique_ptr<Command> cmd)
    : command(std::move(cmd)), isHovered(false), relativeX(0.5f), relativeY(0.5f), baseCharSize(24) 
{
    text.setFont(font);
    text.setString(textString);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(baseCharSize);

    background.setFillColor(normalColor);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(outlineThickness);

    // Center the origin of the text for proper scaling and positioning
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
} // test test

bool Button::contains(float x, float y) const 
{
    return background.getGlobalBounds().contains(x, y);
}

void Button::setHover(bool hover) 
{
    if (hover && !isHovered) 
    {
        isHovered = true;
        text.setFillColor(sf::Color::Yellow);
        background.setFillColor(hoverColor);
    }
    else if (!hover && isHovered) 
    {
        isHovered = false;
        text.setFillColor(sf::Color::White);
        background.setFillColor(normalColor);
    }
}

void Button::onClick() 
{
    SoundManager::getInstance().play("buttonclick"); //add

    if (command) 
    {
        command->execute();
    }
}

void Button::resize(const sf::Vector2u& windowSize) 
{
    float widthRatio = windowSize.x / 800.0f;
    unsigned int newSize = static_cast<unsigned int>(baseCharSize * widthRatio);
    if (newSize < 5) newSize = 5;
    text.setCharacterSize(newSize);

    // Re-center text
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    float newX = relativeX * windowSize.x;
    float newY = relativeY * windowSize.y;
    text.setPosition(newX, newY);

    // Update background rectangle around text
    background.setSize({ textBounds.width + 40, textBounds.height + 20 });
    background.setOrigin(background.getSize().x / 2.f, background.getSize().y / 2.f);
    background.setPosition(text.getPosition());
}

void Button::draw(sf::RenderWindow& window) const 
{
    window.draw(background);
    window.draw(text);
}

void Button::setColor(const sf::Color& color)
{
    normalColor = color,
    hoverColor = color;

	background.setFillColor(normalColor);
	background.setOutlineColor(normalColor);
}
