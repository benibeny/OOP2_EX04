#pragma once

#include "SeekingFoodAnimal.h"
#include "Managers/EventManager.h"


#define NORMALMONSTAR_SPEED 100.0f
#define NORMALMONSTAR_SPRITE "balrog.png"


#define START_MAX_TIMER 3.0f // seconds

class NormalMonstar : public SeekingFoodAnimal
{
public:
	NormalMonstar();
	NormalMonstar(float speed, std::string sprite, int numRow, int health);

	virtual void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)override;
	virtual void clicked(int damage, sf::Vector2f mousePos)override;

protected:
	virtual bool tryToEat(GameObject& food)override;

	void handleWaitingTimer(float deltaTime);
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems);


	float m_startTimer;
	float m_turningWaitTimer = 0.0f;
	bool m_isWaitTurning = false;
	

};