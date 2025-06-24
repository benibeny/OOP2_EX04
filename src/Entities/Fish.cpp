#include "Entities/Fish.h"
#include <iostream>
#include "ResourceManager.h"
#include "Entities/Money.h"
#include <iostream>




Fish::Fish(Type foodType,Type myType, sf::Vector2f pos, float speed, std::string textureName,const int sheetRows,const int sheetCols,const int animationRow,const std::string& turningSpriteSheetName)
	:Animal(myType , pos, speed,textureName, sheetRows, sheetCols, animationRow), m_myFoodType(foodType), m_isTurning(false), m_turningFrame(0), m_turningSpriteSheetName(turningSpriteSheetName)
{}




void Fish::checkTurn()
{
	//if turning animation is in progress, skip the check
	if (m_isTurning)
	{
		return;
	}

	if (m_velocity.x > 0 && m_direction != AnimalDirection::Right)
	{
		m_direction = AnimalDirection::Right;
		/*m_sprite.setScale(-std::abs(m_sprite.getScale().x), m_sprite.getScale().y);
		m_sprite.setPosition(getPosition().x + m_sprite.getGlobalBounds().width, getPosition().y);*/
		handleTurnAnimation();
	}
	else if (m_velocity.x < 0 && m_direction != AnimalDirection::Left)
	{
		m_direction = AnimalDirection::Left;
		
		/*m_sprite.setScale(std::abs(m_sprite.getScale().x), m_sprite.getScale().y);
		m_sprite.setPosition(getPosition().x - m_sprite.getGlobalBounds().width, getPosition().y);*/
		handleTurnAnimation();
	}
}


void Fish::handleTurnAnimation()
{
	m_isTurning = true;
	m_turningFrame = 0;
	m_speed /= 3.0f; // Reduce speed during turning animation

	m_animationTimer = 0.0f; // Reset animation timer

	//sf::Vector2f currentScale = m_sprite.getScale();
	//ResourceManager::getInstance().getInstance().setSpriteTextureFromSheet(m_sprite, m_turningSpriteSheetName, 0, m_fishSpriteRow);
}


void Fish::foodEatenIncrement(std::pair<int,int> foodValue)
{
	foodEaten += foodValue.second + 30;

	m_health += foodValue.first + FISH_HUNGER;
}


bool Fish::seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems)
{
	bool foundFood = false;
	//pointer to pointer to avoid copying the vector
	std::vector<GameObject*> filteredFood;

	for (const auto& foodItem : foodItems)
	{
		if (foodItem && !foodItem->isDestroyed() && foodItem->getType() == m_myFoodType) 
		{
			filteredFood.push_back(foodItem.get());
		}
	}

	

	if (!filteredFood.empty()) 
	{
		const GameObject* foundClosestFood = findClosestFood(filteredFood);

		moveTowardFood(foundClosestFood);
		foundFood = true;
	}
	
	return foundFood;
}


void Fish::handleHungerTimer(float deltaTime)
{
	m_hungerTimer += deltaTime;
	if (m_hungerTimer >= 0.5f) //fish starves after 1 second without food
	{
		m_hungerTimer = 0.0f; // Reset hunger timer
		m_health -= 1; // Decrease health due to hunger
		if (m_health <= 0) 
		{
			m_shouldDestroy = true; // Mark fish as dead if health drops to zero
		}
	}

}


GameObject* Fish::findClosestFood(const std::vector<GameObject*> foodItems)
{
	if (foodItems.empty())
	{
		return nullptr;
	}

	GameObject* closestFood = nullptr;
	float closestDistance = std::numeric_limits<float>::max();
	sf::Vector2f fishCenter = getCenter();	
	
	for(GameObject* foodItem : foodItems)
	{
		if (foodItem) 	
		{
			sf::Vector2f foodCenter = foodItem->getCenter();
			sf::Vector2f diffrence = foodCenter - fishCenter;

			float distance = std::sqrt(diffrence.x * diffrence.x + diffrence.y * diffrence.y);

			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestFood = foodItem;
			}
		}
	}
	return closestFood;	

}

void Fish::moveTowardFood(const GameObject* food)
{
	sf::Vector2f fishCenter = getCenter();
	sf::Vector2f foodCenter = food->getCenter();
	sf::Vector2f direction = foodCenter - fishCenter;

	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 0)
	{
		direction /= magnitude;
		m_velocity = direction * m_speed;
	}
}