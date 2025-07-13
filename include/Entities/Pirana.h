#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Fish.h"
#include "Managers/EventManager.h"
#include "Managers/ResourceManager.h"

//becasuse it send un set thing so we use define to make it global
#define PIRANA_SPEED 150.0f



class Pirana : public Fish
{
public:
	Pirana(sf::Vector2f pos);

	void update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& foods, sf::Vector2u& windowSize) override;
	void shouldProduceMoney(float deltaTime) override;
	void foodEatenIncrement(std::pair<int, int> foodValue = std::pair<int, int>(0, 0))override;
	virtual bool tryToEat(GameObject& food)override;
	int getDeathRow() const override;

	//double dispatch
	virtual bool canBeEatenBy(const NormalMonstar& monster)override;
private:
	Money::Moneytype getProducedMoneyType()override;

};