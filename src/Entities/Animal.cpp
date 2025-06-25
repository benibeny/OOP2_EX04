#include "Entities/Animal.h"
#include <limits>
#include <iostream>
Animal::Animal(Type myType, sf::Vector2f pos, float speed, std::string textuerName, const int sheetRows, const int sheetCols, const int animationRow)
	: GameObject(myType,pos, textuerName, sheetRows, sheetCols, animationRow), m_speed(speed), m_velocity(0.f,0.f),
	m_random(std::random_device{}()), m_randomDirection(-1.0f, 1.0f)
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

	float shopBarHeight = windowSize.x / 9.0f;
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


void Animal::moveRandomly(float deltaTime)
{

	m_directionChangeTime += deltaTime;
	if (m_directionChangeTime > 2.0f) // Change direction every second
	{
		m_velocity.x = m_randomDirection(m_random) * m_speed; // Random speed in x direction
		m_velocity.y = m_randomDirection(m_random) * m_speed * 0.5f;
		m_directionChangeTime = 0.0f;

		//checkTurn();
	}
}


void Animal::checkTurn()
{

	if (m_velocity.x > 0 && m_direction != AnimalDirection::Right)
	{
		m_direction = AnimalDirection::Right;
		m_sprite.setScale(-std::abs(m_sprite.getScale().x), m_sprite.getScale().y);
		m_sprite.setPosition(getPosition().x + m_sprite.getGlobalBounds().width, getPosition().y);
		
	}
	else if (m_velocity.x < 0 && m_direction != AnimalDirection::Left)
	{
		m_direction = AnimalDirection::Left;

		m_sprite.setScale(std::abs(m_sprite.getScale().x), m_sprite.getScale().y);
		m_sprite.setPosition(getPosition().x - m_sprite.getGlobalBounds().width, getPosition().y);
		
	}
}