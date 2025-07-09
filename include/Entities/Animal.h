#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <random>

#include "Entities/GameObject.h"


//snail ,fish 
class Animal : public GameObject
{
public:
	Animal(sf::Vector2f pos, float speed,std::string textuerName, const int sheetRows, const int sheetCols, const int animationRow);
	virtual ~Animal() = default;

	void swapDirection();
	sf::Vector2f getVelocity() const { return m_velocity; }
	
	float getHealth() const { return m_health; }
	void setHealth(float health) { m_health = health; }
	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; }


protected:
	virtual void checkTurn();
	void bounceOffWalls(const sf::Vector2u& windowSize);
	void moveRandomly(float deltaTime);
	

	enum class AnimalDirection
	{
		Left,
		Right
	};

	AnimalDirection m_direction = AnimalDirection::Left;

	float m_speed;
	sf::Vector2f m_velocity;
	
	float m_health = 30.0f;

	//heavy use as member and not local variable to avoid re-seeding
	float m_directionChangeTime = 2.0f;
	mutable std::mt19937 m_random;
	mutable std::uniform_real_distribution<float> m_randomDirection;
};


