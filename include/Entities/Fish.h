#pragma once
#include <random>
#include <list>	

#include "Entities/Money.h"
#include "SeekingFoodAnimal.h"


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
	
	void checkTurn()override;
	virtual void handleTurnAnimation();


	virtual void foodEatenIncrement(std::pair<int, int> foodValue = std::pair<int,int>(0,0));
	int getFoodEaten() const { return foodEaten; }
	

	void handleHungerTimer(float deltaTime);
	bool isHungry() const { return m_health <= float(m_fishStartHunger); }
	//virtual bool shouldProduceMoney() const;
	//void resetMoneyTimer() override;

	

	virtual void shouldProduceMoney(float deltaTime) = 0;
	

protected:
	virtual Money::Moneytype getProducedMoneyType() = 0;

	virtual int getDeathRow() const = 0; 


	int foodEaten = 0;
	float m_hungerTimer = 0.0f;
	int m_fishStartHunger = 30;//can change for every fish
	

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

	bool updateDeathAnimation(float deltaTime);




};