#pragma once

#include "SeekingFoodAnimal.h"
#include "EventManager.h"


#define NORMALMONSTAR_SPEED 100.0f
#define NORMALMONSTAR_SPRITE "balrog.png"


#define START_MAX_TIMER 3.0f // seconds

class NormalMonstar : public SeekingFoodAnimal
{
public:
	NormalMonstar();

	void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)override;
	void clicked(int damage, sf::Vector2f mousePos)override;

private:
	virtual bool tryToEat(GameObject& food)override;

	void handleWaitingTimer(float deltaTime);
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems);


	float m_startTimer;
	float m_turningWaitTimer = 0.0f;
	bool m_isWaitTurning = false;
	

};