#include "Entities/HelperSeekCoin.h"

HelperSeekCoin::HelperSeekCoin(std::string spriteSheet, float speed)
	:SeekingFoodAnimal(sf::Vector2f(500.0f, 500.0f), speed, spriteSheet, 1, 10, 0)//all helpers are row 1 and 10 frames
{}


void HelperSeekCoin::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{
	move(windowSize, deltaTime, foodItems);

	updateAnimation(deltaTime);

}

bool HelperSeekCoin::tryToEat(GameObject& food)
{
	return food.canBeEatenBy(*this);
}

bool HelperSeekCoin::canBeEatenBy(const NormalMonstar& monster)
{
	return true;
}


void HelperSeekCoin::move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems)
{

	if (!seekFood(foodItems))
	{
		moveRandomly(deltaTime);
	}


	sf::Vector2f currentPos = m_sprite.getPosition();
	sf::Vector2f newPos = currentPos + m_velocity * deltaTime;
	m_sprite.setPosition(newPos);

	bounceOffWalls(windowSize);
	checkTurn();
}
