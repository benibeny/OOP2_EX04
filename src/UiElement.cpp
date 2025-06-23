#include "UiElement.h"


UiElement::UiElement(std::string spriteName, const int rows, const int cols)
	:m_position(0.0f,0.0f), m_size(1.0f, 1.0f), m_spriteName(spriteName)
{


	ResourceManager &resource = ResourceManager::getInstance();
	resource.loadSpriteSheet(spriteName, cols, rows);
	resource.setSpriteTextureFromSheet(m_sprite,spriteName, 0, 0);
	/*m_sprite.setPosition(m_position);
	m_sprite.setScale(m_size);*/
}


void UiElement::setSize(const float width ,const float highet)
{
	m_size = sf::Vector2f(width, highet);
	sf::FloatRect bounds = m_sprite.getLocalBounds();
	
	if (bounds.width > 0 && bounds.height > 0)
	{
		m_sprite.setScale(width / bounds.width, highet / bounds.height);
	}


}

void UiElement::setPosition(const sf::Vector2f& position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

sf::Vector2f UiElement::getPosition() const 
{
	return m_position;
}

sf::Vector2f UiElement::getSize() const
{
	return m_size;
}

void UiElement::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}


bool UiElement::isMouseOver(const sf::Vector2f& mousePosition) const
{
	return m_sprite.getGlobalBounds().contains(mousePosition);
}
