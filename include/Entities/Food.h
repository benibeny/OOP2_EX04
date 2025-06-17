#pragma once	
#include "ResourceManager.h"
#include "Entities/Eatable.h"
#include <SFML/Graphics.hpp>


#define FOOD_SPRITE_SHEET_NAME "food.png"

class Food : public Eatable
{
public:
	
	enum class Foodtype
	{
		Worst,
		Medium,
		Best
	};

	void update(float deltaTime, const std::vector <std::unique_ptr<Eatable>>& foodItems, sf::Vector2u& windowSize) override;
	Food(Foodtype foodType ,const sf::Vector2f pos);
	void destroyTouchedFloor(sf::Vector2u& windowSize);
	std::pair<int, int> foodEaten();




private:
	const sf::Vector2f m_velocity = sf::Vector2f(0.0f,50.0f);

	int m_healthValueGives;
	int m_sizeValueGives;

	Foodtype m_foodType;

};