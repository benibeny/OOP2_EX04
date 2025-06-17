#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Entities/Eatable.h"


//snail ,fish 
class Animal : public Eatable
{
public:
	Animal(Type myType, sf::Vector2f pos, float speed,std::string textuerName, const int sheetRows, const int sheetCols, const int animationRow);
	virtual ~Animal() = default;

	virtual void handleCollision(Eatable* food) = 0;
	//virtual std::string getType() const = 0;


	void swapDirection();
	sf::Vector2f getVelocity() const { return m_velocity; }
	
	float getHealth() const { return m_health; }
	void setHealth(float health) { m_health = health; }
	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }

protected:
	void bounceOffWalls(const sf::Vector2u& windowSize);
	

	enum class AnimalDirection
	{
		Left,
		Right
	};
	AnimalDirection m_direction = AnimalDirection::Left;

	float m_speed;
	sf::Vector2f m_velocity;
	
	float m_health = 30.0f;

};
