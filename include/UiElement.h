#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <string>

//shopbar element
class UiElement 
{
public:
	UiElement(std::string spriteName,const int rows,const int cols,const int currentRow = 0);
	virtual ~UiElement() = default;

	void setSize(const float width, const float highet);

	virtual void setPosition(const sf::Vector2f& position);
	
	sf::Vector2f getPosition() const;
	sf::Vector2f getSize() const;
	virtual void draw(sf::RenderWindow& window) const;
	virtual bool isMouseOver(const sf::Vector2f& mousePosition) const;
	
protected:
	sf::Vector2f m_position;
	sf::Vector2f m_size;

	sf::Sprite m_sprite;
	std::string m_spriteName;


};