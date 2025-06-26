#include "Entities/Pirana.h"


Pirana::Pirana(sf::Vector2f pos)
	:Fish(pos, PIRANA_SPEED, MOVE_ONE_DIRC_SPRITE_NAME, 5, MAX_FRAMES, 4, TURNING_SPRITE_NAME)
	,m_swimingFrame(0)
{
	ResourceManager::getInstance().loadSpriteSheet(TURNING_SPRITE_NAME, MAX_FRAMES, 5);


	//maybe change to update fishsize
	m_sprite.setScale(1.2f, 1.2f);

	m_random.seed(std::random_device{}());
}


void Pirana::update(float deltaTime, const std::list <std::unique_ptr<GameObject>>& foodItems, sf::Vector2u& windowSize)
{
	handleHungerTimer(deltaTime);
	move(windowSize, deltaTime, foodItems);

	shouldProduceMoney(deltaTime);

	updateAnimation(deltaTime);
}


void Pirana::updateAnimation(float deltaTime)
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
				m_speed = PIRANA_SPEED;
				ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, MOVE_ONE_DIRC_SPRITE_NAME, m_swimingFrame, 4);


				applyDirectionScale();


			}
			else
			{
				ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, TURNING_SPRITE_NAME, m_turningFrame, 4);
				m_turningFrame++;
			}
			m_animationTimer = 0.0f;
		}

	}
	else if (m_animationTimer >= 0.2f)
	{
		m_swimingFrame = (m_swimingFrame + 1) % MAX_FRAMES;
		ResourceManager::getInstance().setSpriteTextureFromSheet(m_sprite, MOVE_ONE_DIRC_SPRITE_NAME, m_swimingFrame, 4);

		m_animationTimer = 0.0f;
	}
}

void Pirana::foodEatenIncrement(std::pair<int, int> foodValue)
{
	m_health += 50; //pirana hunger
}

void Pirana::move(sf::Vector2u& windowSize, float deltaTime, const std::list<std::unique_ptr<GameObject>>& eatable)
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

void Pirana::shouldProduceMoney(float deltaTime)
{
	if (m_coinTimer >= COIN_TIMER)
	{
		sf::Vector2f center = m_sprite.getPosition() + sf::Vector2f(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
		m_coinTimer = 0;
		EventManager::getInstance().notifyCreateMoney(int(getProducedMoneyType()), center);
	}
	m_coinTimer += deltaTime;// Update coin timer
}


Money::Moneytype Pirana::getProducedMoneyType()
{
	return Money::Moneytype::Diamond;
}




void Pirana::applyDirectionScale()
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



bool Pirana::tryToEat(GameObject& food)
{
	return food.canBeEatenBy(*this);
}


bool Pirana::canBeEatenBy(const NormalMonstar& monster)
{
	return true; // Pirana can be eaten by any NormalMonstar
}