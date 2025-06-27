#include "Entities/Fish.h"
#include <iostream>
#include <string>
#include "ResourceManager.h"
#include "Entities/Money.h"





Fish::Fish( sf::Vector2f pos, float speed, std::string textureName,const int sheetRows,const int sheetCols,const int animationRow,const std::string& turningSpriteSheetName)
	:SeekingFoodAnimal(pos, speed,textureName, sheetRows, sheetCols, animationRow), m_isTurning(false), m_turningFrame(0), m_turningSpriteSheetName(turningSpriteSheetName)
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
	foodEaten += foodValue.second + 10;

	m_health += foodValue.first + m_fishStartHunger;
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


