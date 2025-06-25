#pragma once

#include "Animal.h"
#include "EventManager.h"


#define NORMALMONSTAR_SPEED 100.0f
#define NORMALMONSTAR_SPRITE "balrog.png"


#define START_MAX_TIMER 3.0f // seconds

class NormalMonstar : public Animal 
{
public:
	NormalMonstar();

	void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)override;
	void handleCollision(GameObject* food)override {}


	bool seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems);
	void moveTowardFood(const GameObject* food);
	GameObject* findClosestFood(const std::vector<GameObject*> foodItems);
	void clicked(int damage, sf::Vector2f mousePos)override;

private:
	//GameObject* findClosestFood(const std::vector<GameObject*> foodItems);
	//void moveTowardFood(const GameObject* food);
	void handleWaitingTimer(float deltaTime);
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems);


	float m_startTimer;
	float m_turningWaitTimer = 0.0f;
	bool m_isWaitTurning = false;
	

};