#include "Button.h"
#include <SFML/Graphics.hpp>
#include "SoundManager.h"

Button::Button(const std::string& textString, sf::Font& m_font, std::unique_ptr<Command> cmd)
    : command(std::move(cmd)), isHovered(false), relativeX(0.5f), relativeY(0.5f), baseCharSize(24) 
{
	sf::Texture* resourceTexture = ResourceManager::getInstance().getTexture("button.png");
    if (resourceTexture) 
    {
        background.setTexture(resourceTexture);
    }
    else 
    {
        background.setFillColor(normalColor);
        background.setOutlineColor(sf::Color::White);
        background.setOutlineThickness(outlineThickness);
    }
    
    text.setFont(m_font);
    text.setString(textString);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(baseCharSize);

    

    // Center the origin of the text for proper scaling and positioning
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
}

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
    }
    else if (!hover && isHovered) 
    {
        isHovered = false;
        text.setFillColor(sf::Color::White);
    }
}

void Button::onClick() 
{
    SoundManager::getInstance().play("buttonclick");

    if (command) 
    {
        command->execute();
    }
}

void Button::resize(const sf::Vector2u& windowSize) 
{
    float widthRatio = windowSize.x / 900.0f;
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
    background.setSize({ textBounds.width + 75, textBounds.height + 50 });
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
	background.setTexture(nullptr); // Remove texture if set
    normalColor = color,
    hoverColor = color;

	background.setFillColor(normalColor);
	background.setOutlineColor(normalColor);
}
