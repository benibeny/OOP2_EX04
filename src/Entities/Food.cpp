#include "Entities/Food.h"
#include <iostream>

Food::Food(Foodtype foodType ,const sf::Vector2f pos)
	:Eatable(Type::Food, pos, FOOD_SPRITE_SHEET_NAME, 5, 10, int(foodType),20), m_foodType(foodType)
{
	m_sprite.setScale(1.5f, 1.5f);

	switch (m_foodType)
	{
		case Foodtype::Worst:
			m_healthValueGives = 6;
			m_sizeValueGives = 6;
			break;

		case Foodtype::Medium:
			m_healthValueGives = 6;
			m_sizeValueGives = 12;
			break;

		case Foodtype::Best:
			m_healthValueGives = 12;
			m_sizeValueGives = 12;
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
		m_isEaten = true;
	}

}

//TODO : mplement struct to return 2 valuse for food and size
//do both signal eaten and give value
std::pair<int,int> Food::foodEaten()
{
	if (!isEaten())
	{
		m_isEaten = true;
		return std::pair<int,int>(m_healthValueGives, m_sizeValueGives);
	}
	return std::pair<int, int>(0,0);
}




void Food::update(float deltaTime, const std::vector <std::unique_ptr<Eatable>>& foodItems, sf::Vector2u& windowSize) 
{
	if (!m_isEaten)
	{
		sf::Vector2f currentPos = getPosition();
		sf::Vector2f newPos = currentPos + m_velocity * deltaTime;

		setPosition(newPos);

		updateAnimation(deltaTime);
		destroyTouchedFloor(windowSize);
	}
}



