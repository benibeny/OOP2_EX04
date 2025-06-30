#include "Entities/Food.h"
#include <iostream>
#include "SoundManager.h"

Food::Food(Foodtype foodType ,const sf::Vector2f pos)
	:GameObject(pos, FOOD_SPRITE_SHEET_NAME, 5, 10, int(foodType),20), m_foodType(foodType)
{
	m_sprite.setScale(1.5f, 1.5f);

	SoundManager::getInstance().play("drop"); //add

	switch (m_foodType)
	{
		case Foodtype::Worst:
			m_healthValueGives = 6;
			m_sizeValueGives = 3;
			break;

		case Foodtype::Medium:
			m_healthValueGives = 6;
			m_sizeValueGives = 4;
			break;

		case Foodtype::Best:
			m_healthValueGives = 8;
			m_sizeValueGives = 5;
			break;

		default:
			m_healthValueGives = 0;
			m_sizeValueGives = 0;
			break;
	}
	
}


void Food::destroyTouchedFloor(sf::Vector2u& windowSize)
{
	sf::Vector2f position = m_sprite.getPosition();
	sf::FloatRect bounds = m_sprite.getGlobalBounds();

	
	float sandBarHeight = windowSize.y / 10.0f;
	

	
	if (position.y + bounds.height > (windowSize.y - sandBarHeight))
	{
		setDestroyed(true);
	}

}

//TODO : mplement struct to return 2 valuse for food and size
//do both signal eaten and give value
std::pair<int,int> Food::foodEaten()
{
	if (!isDestroyed())
	{
		setDestroyed(true);
		return std::pair<int,int>(m_healthValueGives, m_sizeValueGives);
	}
	return std::pair<int, int>(0,0);
}




void Food::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{
	if (!m_shouldDestroy)
	{
		sf::Vector2f currentPos = getPosition();
		sf::Vector2f newPos = currentPos + m_velocity * deltaTime;

		setPosition(newPos);

		updateAnimation(deltaTime);
		destroyTouchedFloor(windowSize);
	}
}



void Food::setDestroyed(bool destroyed)
{
	GameObject::setDestroyed(destroyed);
	EventManager::getInstance().notifyFoodDestroyed();
}


bool Food::canBeEatenBy(const GoldFish& goldFish)
{
	return true; // All food can be eaten by the GoldFish
}