#include "Entities/HelperSnail.h"

HelperSnail::HelperSnail()
	:HelperSeekCoin(HELPER_SNAIL_SPRITE, HELPER_SNAIL_SPEED)
{}


void HelperSnail::move(sf::Vector2u& windowSize, float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems)
{
	if (!seekFood(foodItems))
	{
		moveRandomly(deltaTime);
	}


	sf::Vector2f currentPos = m_sprite.getPosition();
	sf::Vector2f newPos = currentPos + m_velocity * deltaTime;
	

	float sandBarHeight = windowSize.y / 10.0f;
	newPos.y = windowSize.y - sandBarHeight + 0.1f;
	setPosition(newPos);

	bounceOffWalls(windowSize);
	checkTurn();
}