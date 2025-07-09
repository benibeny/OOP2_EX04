#include "Entities/Fish.h"
#include <iostream>
#include <string>
#include "ResourceManager.h"
#include "Entities/Money.h"
#include "SoundManager.h"





Fish::Fish( sf::Vector2f pos, float speed, std::string textureName,const int sheetRows,const int sheetCols,const int animationRow,const std::string& turningSpriteSheetName)
	:SeekingFoodAnimal(pos, speed,textureName, sheetRows, sheetCols, animationRow)
	,m_isTurning(false), m_turningFrame(0), m_normalSpeed(speed), m_turningSpriteSheetName(turningSpriteSheetName)
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
		handleTurnAnimation();
	}
	else if (m_velocity.x < 0 && m_direction != AnimalDirection::Left)
	{
		m_direction = AnimalDirection::Left;
		handleTurnAnimation();
	}
}


void Fish::handleTurnAnimation()
{
	m_isTurning = true;
	m_turningFrame = 0;
	m_speed /= 3.0f; // Reduce speed during turning animation

	m_animationTimer = 0.0f; // Reset animation timer
}


void Fish::foodEatenIncrement(std::pair<int,int> foodValue)
{
	SoundManager::getInstance().play("eat"); 

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

		if (m_health <= 0 && !m_isDying)
		{
			SoundManager::getInstance().play("die");

			m_isDying = true;
			m_deathTimer = 0.0f;
			m_deathFrame = 0;
			m_deathAnimDone = false;
			m_velocity = sf::Vector2f(0.f, 0.f);  // stop movement

			// set first death frame
			sf::Vector2f currentScale = m_sprite.getScale();
			ResourceManager::getInstance().setSpriteTextureFromSheet(
				m_sprite, "smalldie.png", 0, getDeathRow());
				m_sprite.setScale(1.4f, 1.4f);
		}
	}
}


bool Fish::updateDeathAnimation(float deltaTime) {
	if (!m_isDying)
		return false;

	const float frameDuration = 0.2f;
	m_deathTimer += deltaTime;

	if (!m_deathAnimDone && m_deathTimer >= frameDuration) 
	{
		ResourceManager::getInstance().setSpriteTextureFromSheet(
			m_sprite, "smalldie.png", m_deathFrame, getDeathRow()
		);
		m_deathFrame++;
		m_deathTimer -= frameDuration;

		if (m_deathFrame >= 10) 
		{
			m_deathAnimDone = true;
			m_deathTimer = 0.0f;  // reset for fade-out
		}
	}
	else if (m_deathAnimDone) 
	{
		float fadeDuration = 2.0f;
		float alphaRatio = 1.0f - (m_deathTimer / fadeDuration);

		if (alphaRatio <= 0.0f) 
		{
			setDestroyed(true);
		}
		else 
		{
			sf::Color color = m_sprite.getColor();
			color.a = static_cast<sf::Uint8>(255 * alphaRatio);
			m_sprite.setColor(color);
		}
	}
	return true;
}



void Fish::move(sf::Vector2u& windowSize, float deltaTime, const std::list<std::unique_ptr<GameObject>>& eatable)
{
	if (m_health <= m_fishStartHunger && !eatable.empty())
	{
		// Try to seek food; if not successful, move randomly
		if (!seekFood(eatable))
		{
			moveRandomly(deltaTime);
		}
	}
	else
	{
		// Not hungry or no food: move randomly
		moveRandomly(deltaTime);
	}

	checkTurn();

	sf::Vector2f currentPos = m_sprite.getPosition();
	sf::Vector2f newPos = currentPos + m_velocity * deltaTime;
	m_sprite.setPosition(newPos);

	bounceOffWalls(windowSize);
}



void Fish::applyDirectionScale()
{
	sf::Vector2f currentScale = m_sprite.getScale();

	float scaleValue = std::abs(currentScale.x);

	sf::Vector2f currentPosition = m_sprite.getPosition();
	if (m_direction == AnimalDirection::Left)
	{
		if (currentScale.x < 0)
		{
			m_sprite.setScale(scaleValue, scaleValue);
			m_sprite.setPosition(currentPosition.x - m_sprite.getGlobalBounds().width, currentPosition.y);
		}
	}
	else if (m_direction == AnimalDirection::Right)
	{
		if (currentScale.x > 0)
		{
			m_sprite.setScale(-scaleValue, scaleValue);
			m_sprite.setPosition(currentPosition.x + m_sprite.getGlobalBounds().width, currentPosition.y);
		}
	}

}


void Fish::updateAnimation(float deltaTime)
{
	m_animationTimer += deltaTime;
	if (m_isTurning)
	{
		if (m_animationTimer >= 0.1f)
		{
			//animation is over
			if (m_turningFrame >= MAX_FRAMES)
			{
				m_isTurning = false;
				m_turningFrame = 0;
				m_swimingFrame = 0;
				m_speed = m_normalSpeed;
				ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, MOVE_ONE_DIRC_SPRITE_NAME, m_swimingFrame, m_sheetRowIndex);


				applyDirectionScale();
			}
			else
			{
				ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, TURNING_SPRITE_NAME, m_turningFrame, m_sheetRowIndex);
				m_turningFrame++;
			}
			m_animationTimer = 0.0f;
		}

	}
	else if (m_animationTimer >= 0.2f)
	{
		m_swimingFrame = (m_swimingFrame + 1) % MAX_FRAMES;
		ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, MOVE_ONE_DIRC_SPRITE_NAME, m_swimingFrame, m_sheetRowIndex);

		m_animationTimer = 0.0f;
	}
}