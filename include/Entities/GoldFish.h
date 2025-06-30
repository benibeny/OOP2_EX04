#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Fish.h"
#include "EventManager.h"

#include "ResourceManager.h"

//becasuse it send un set thing so we use define to make it global
#define MOVE_ONE_DIRC_SPRITE_NAME "smallswim.png"
#define TURNING_SPRITE_NAME "smallFish2.png"
#define GOLDFISH_SPEED 150.0f
#define MAX_FRAMES 10



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
	void updateAnimation(float deltaTime);
	//void getFishSize(Size size);
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list<std::unique_ptr<GameObject>>& foods);
	
	void shouldProduceMoney(float deltaTime) override;



	
	//double dispatch
	virtual bool canBeEatenBy(const Pirana& pirana)override;
	virtual bool canBeEatenBy(const NormalMonstar& monster)override;

	//bool seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems)override;

	int getDeathRow() const override;

private:
	virtual bool tryToEat(GameObject& food)override;

	Money::Moneytype getProducedMoneyType()override;

	void updateFishSize();
	void applyDirectionScale();

	Size m_fishSize;
	int m_swimingFrame;
	
	//size for fish to grow
	static constexpr int BAR_REACH_MEDIUM_FISH_SIZE = 30;
	static constexpr int BAR_REACH_LARGE_FISH_SIZE = 60;

};