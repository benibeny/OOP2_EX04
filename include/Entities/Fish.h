#pragma once
#include <random>
#include <list>	

#include "Entities/Money.h"
#include "Animal.h"


class Fish : public Animal
{
public:
	Fish(Type foodType,Type myType, sf::Vector2f pos, float speed, std::string textureName,
										const int sheetRows,
										const int sheetCols,
										const int animationRow,
										const std::string& turningSpriteSheetName);
		
	


	virtual void update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize) = 0;
	virtual void handleCollision(GameObject* food) {}
	
	void checkTurn();
	virtual void handleTurnAnimation();


	void foodEatenIncrement(std::pair<int, int> foodValue);
	int getFoodEaten() const { return foodEaten; }
	bool seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems);

	void handleHungerTimer(float deltaTime);
	bool isHungry() const { return m_health <= float(FISH_HUNGER); }
	//virtual bool shouldProduceMoney() const;
	//void resetMoneyTimer() override;

	virtual void shouldProduceMoney(float deltaTime) = 0;
	

protected:
	virtual Money::Moneytype getProducedMoneyType() = 0;

	virtual void moveRandomly(float deltaTime);
	GameObject* findClosestFood(const std::vector<GameObject*> foodItems);
	void moveTowardFood(const GameObject* food);

	int foodEaten = 0;
	float m_hungerTimer = 0.0f;
	static const int FISH_HUNGER = 30;

	Type m_myFoodType;

	bool m_isTurning;
	int m_turningFrame;
	std::string m_turningSpriteSheetName;


	float m_coinTimer = 0.0f;
	static constexpr float COIN_TIMER = 5.0f;
	


	//heavy use as member and not local variable to avoid re-seeding
	float m_directionChangeTime = 2.0f;
	mutable std::mt19937 m_random;
	mutable std::uniform_real_distribution<float> m_randomDirection;


};