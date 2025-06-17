#include "Entities/GoldFish.h"


GoldFish::GoldFish(sf::Vector2f pos)
	:Fish(Type::Food ,Type::GoldFish,pos, GOLDFISH_SPEED, MOVE_ONE_DIRC_SPRITE_NAME,5, MAX_FRAMES,2, TURNING_SPRITE_NAME),
	m_fishSize(Size::Small), m_swimingFrame(0)
{
	ResourceManager::getInstance().loadSpriteSheet(TURNING_SPRITE_NAME, MAX_FRAMES, 5);
	

	//maybe change to update fishsize
	m_sprite.setScale(0.8f, 0.8f);

	m_random.seed(std::random_device{}());
}


void GoldFish::update(float deltaTime, const std::vector <std::unique_ptr<Eatable>>& foodItems, sf::Vector2u& windowSize)
{
	updateFishSize();
	handleHungerTimer(deltaTime);
	move(windowSize, deltaTime, foodItems);
	m_coinTimer += deltaTime;// Update coin timer

	
	updateAnimation(deltaTime);
}


void GoldFish::updateAnimation(float deltaTime)
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
				m_speed = GOLDFISH_SPEED;
				ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, MOVE_ONE_DIRC_SPRITE_NAME, m_swimingFrame, 2);

				
				applyDirectionScale();
				

			}
			else 
			{
				ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, TURNING_SPRITE_NAME, m_turningFrame, 2);
				m_turningFrame++;
			}
			m_animationTimer = 0.0f;
		}
		
	}
	else if (m_animationTimer >= 0.2f)
	{
		m_swimingFrame = (m_swimingFrame + 1) % MAX_FRAMES;
		ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, MOVE_ONE_DIRC_SPRITE_NAME,m_swimingFrame, 2);

		m_animationTimer = 0.0f;
	}
}


void GoldFish::move(sf::Vector2u& windowSize,float deltaTime, const std::vector<std::unique_ptr<Eatable>>& eatable)
{
	if (m_health <= FISH_HUNGER && !eatable.empty()) 
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

	////can be dymaimc cast or enum
	//if (!eatable.empty() && m_health <= FISH_HUNGER && !seekFood(eatable))
	//{
	//	//when there is food, fish will move towards it 
	//	moveRandomly(deltaTime);
	//}
	checkTurn();
	


	sf::Vector2f currentPos = m_sprite.getPosition();
	sf::Vector2f newPos = currentPos + m_velocity * deltaTime;
	setPosition(newPos);

	bounceOffWalls(windowSize);
}

Money::Moneytype GoldFish::shouldProduceMoney()
{
	if (m_fishSize != Size::Small && m_coinTimer >= COIN_TIMER)
	{
		m_coinTimer = 0;
		return getProducedMoneyType();
	}
	return Money::Moneytype::Invalid;
}


Money::Moneytype GoldFish::getProducedMoneyType()
{
	if (m_fishSize == Size::Medium)
	{
		return Money::Moneytype::Silver;
	}
	else if (m_fishSize == Size::Large)
	{
		return Money::Moneytype::Gold;
	}

	return Money::Moneytype::Invalid;
}


void GoldFish::updateFishSize()
{
	Size newSize = m_fishSize;
	int foodEaten = getFoodEaten();
	if (foodEaten >= BAR_REACH_LARGE_FISH_SIZE && newSize != Size::Large)
	{
		newSize = Size::Large;
	}
	else if( foodEaten >= BAR_REACH_MEDIUM_FISH_SIZE && foodEaten < BAR_REACH_LARGE_FISH_SIZE && newSize != Size::Medium)
	{
		newSize = Size::Medium;
	}
	
	if (newSize != m_fishSize)
	{
		m_fishSize = newSize;
		float scale = (int)m_fishSize / 10.0f;


		//add becuse the fish was being bugged when it turns to get food with scals
		sf::Vector2f currPos = m_sprite.getPosition();
		sf::Vector2f currScale = m_sprite.getScale();
		
		float newScaleX = (currScale.x < 0) ? -scale : scale;


		m_sprite.setScale(newScaleX, scale);
		m_sprite.setPosition(currPos);
	}
	
}



void GoldFish::applyDirectionScale()
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