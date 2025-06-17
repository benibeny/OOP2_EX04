#include "Entities/Animal.h"
#include <limits>
#include <iostream>
Animal::Animal(Type myType, sf::Vector2f pos, float speed, std::string textuerName, const int sheetRows, const int sheetCols, const int animationRow)
	: Eatable(myType,pos, textuerName, sheetRows, sheetCols, animationRow), m_speed(speed), m_velocity(0.f,0.f)
{}

void Animal::bounceOffWalls(const sf::Vector2u& windowSize)
{
	
	sf::Vector2f position = m_sprite.getPosition();
	sf::FloatRect bounds = m_sprite.getGlobalBounds();

	if (position.x <= 0)
	{
		//swapDirection();
		position.x = 0;
		//m_velocity.x = std::abs(m_velocity.x);
		
	}
	else if (position.x  > windowSize.x)
	{
		//swapDirection();
		position.x = windowSize.x;
		//m_velocity.x = -std::abs(m_velocity.x);
		
	}

	float shopBarHeight = windowSize.y / 10.0f;
	float sandBarHeight = windowSize.y / 10.0f;

	if( position.y <= shopBarHeight)
	{
		position.y = shopBarHeight;
		m_velocity.y = std::abs(m_velocity.y);
	}
	else if (position.y + bounds.height > (windowSize.y - sandBarHeight))
	{
		position.y = windowSize.y - sandBarHeight - bounds.height;
		m_velocity.y = -std::abs(m_velocity.y);
	}

	m_sprite.setPosition(position);
}


void Animal::swapDirection()
{
	if (m_direction == AnimalDirection::Left)
	{
		m_direction = AnimalDirection::Right;
	}
	else
	{
		m_direction = AnimalDirection::Left;
	}

	m_sprite.setScale(-m_sprite.getScale().x, m_sprite.getScale().y);
}

