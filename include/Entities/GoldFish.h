#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Fish.h"
#include "EventManager.h"

#include "ResourceManager.h"


#define GOLDFISH_SPEED 150.0f



class GoldFish : public Fish
{
public:
	enum class Size
	{
		Small = 8,
		Medium = 10,
		Large = 12
	};



	GoldFish(sf::Vector2f pos);
		
	void update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& foods, sf::Vector2u& windowSize) override;
	
	void shouldProduceMoney(float deltaTime) override;


	//double dispatch
	virtual bool canBeEatenBy(const Pirana& pirana)override;
	virtual bool canBeEatenBy(const NormalMonstar& monster)override;


	int getDeathRow() const override;

private:
	virtual bool tryToEat(GameObject& food)override;
	Money::Moneytype getProducedMoneyType()override;
	void updateFishSize();

	//size for fish to grow
	static constexpr int BAR_REACH_MEDIUM_FISH_SIZE = 30;
	static constexpr int BAR_REACH_LARGE_FISH_SIZE = 60;

	Size m_fishSize;
	
};