#pragma once
#include <random>
#include <list>	

#include "Entities/Money.h"
#include "SeekingFoodAnimal.h"


#define MOVE_ONE_DIRC_SPRITE_NAME "smallswim.png"
#define TURNING_SPRITE_NAME "smallFish2.png"

#define MAX_FRAMES 10

class Fish : public SeekingFoodAnimal
{
public:
	Fish(sf::Vector2f pos, float speed, std::string textureName,
										const int sheetRows,
										const int sheetCols,
										const int animationRow,
										const std::string& turningSpriteSheetName);
		
	virtual void update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize) = 0;
	virtual void handleCollision(GameObject* food) {}
	virtual void foodEatenIncrement(std::pair<int, int> foodValue = std::pair<int,int>(0,0));
	int getFoodEaten() const { return foodEaten; }
	bool isHungry() const { return m_health <= float(m_fishStartHunger); }
	virtual void shouldProduceMoney(float deltaTime) = 0;

protected:
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list<std::unique_ptr<GameObject>>& eatable);
	void handleHungerTimer(float deltaTime);
	void checkTurn()override;
	virtual void handleTurnAnimation();
	virtual Money::Moneytype getProducedMoneyType() = 0;
	void applyDirectionScale();
	void updateAnimation(float deltaTime)override;
	bool updateDeathAnimation(float deltaTime);
	virtual int getDeathRow() const = 0; 


	int foodEaten = 0;
	float m_hungerTimer = 0.0f;
	int m_fishStartHunger = 30;//can change for every fish
	int m_swimingFrame = 0;
	float m_normalSpeed;

	bool m_isTurning;
	int m_turningFrame;
	std::string m_turningSpriteSheetName;


	float m_coinTimer = 0.0f;
	float m_maxCoinTimer = 12.0f;//can change for every fish
	
	// Death animation state
	bool m_isDying = false;         // Is the fish in dying state
	float m_deathTimer = 0.0f;      // Time since death started
	int m_deathFrame = 0;           // Current frame in death animation
	bool m_deathAnimDone = false;   // Did we finish the death animation

	




};