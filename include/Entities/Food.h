#pragma once	
#include "ResourceManager.h"
#include "Entities/GameObject.h"
#include "EventManager.h"
#include <SFML/Graphics.hpp>


#define FOOD_SPRITE_SHEET_NAME "food.png"

class Food : public GameObject
{
public:
	
	enum class Foodtype
	{
		Worst,
		Medium,
		Best
	};

	void update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize) override;
	Food(Foodtype foodType ,const sf::Vector2f pos);
	void destroyTouchedFloor(sf::Vector2u& windowSize);
	std::pair<int, int> foodEaten();


	void setDestroyed(bool destroyed) override;

private:
	const sf::Vector2f m_velocity = sf::Vector2f(0.0f,50.0f);

	int m_healthValueGives;
	int m_sizeValueGives;

	Foodtype m_foodType;

};