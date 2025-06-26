#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Fish.h"
#include "EventManager.h"

#include "ResourceManager.h"

//becasuse it send un set thing so we use define to make it global
#define MOVE_ONE_DIRC_SPRITE_NAME "smallswim.png"
#define TURNING_SPRITE_NAME "smallFish2.png"
#define PIRANA_SPEED 150.0f
#define MAX_FRAMES 10



class Pirana : public Fish
{
public:
	

	Pirana(sf::Vector2f pos);

	void update(float deltaTime, const std::list<std::unique_ptr<GameObject>>& foods, sf::Vector2u& windowSize) override;
	void updateAnimation(float deltaTime);
	void move(sf::Vector2u& windowSize, float deltaTime, const std::list<std::unique_ptr<GameObject>>& foods);

	void shouldProduceMoney(float deltaTime) override;
	void foodEatenIncrement(std::pair<int, int> foodValue = std::pair<int, int>(0, 0))override;

	virtual bool tryToEat(GameObject& food)override;
	//double dispatch
	virtual bool canBeEatenBy(const NormalMonstar& monster)override;

	
private:
	//std::string getSpriteNameForSize(const Size size);
	//void updateSpriteDirection(float deltaTime);
	Money::Moneytype getProducedMoneyType()override;



	//void updateFishSize();
	void applyDirectionScale();

	int m_swimingFrame;

	//size for fish to grow
	/*static constexpr int BAR_REACH_MEDIUM_FISH_SIZE = 30;
	static constexpr int BAR_REACH_LARGE_FISH_SIZE = 60;*/



};