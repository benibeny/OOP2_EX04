#include "Entities/NormalMonstar.h"
#include "Managers/SoundManager.h"

NormalMonstar::NormalMonstar()
	:SeekingFoodAnimal(sf::Vector2f(900.0f,400.0f), NORMALMONSTAR_SPEED, NORMALMONSTAR_SPRITE,2,10,0),m_startTimer(0.0f)
{
	m_health = 100;
	m_sprite.setScale(1.3f,1.3f);
	SoundManager::getInstance().play("roar");
}

NormalMonstar::NormalMonstar(float speed, std::string sprite, int numRow,int health)
	:SeekingFoodAnimal(sf::Vector2f(900.0f, 400.0f), speed, sprite, numRow, 10, 0), m_startTimer(0.0f)
{
	m_health = health;
	m_sprite.setScale(1.3f, 1.3f);
}

void NormalMonstar::update(float deltaTime, 
						   const std::list <std::unique_ptr<GameObject>>& foodItems,
						   sf::Vector2u& windowSize) 
{
	if (m_isWaitTurning)
	{
		handleWaitingTimer(deltaTime);
	}

	move(windowSize, deltaTime, foodItems);
	
	updateAnimation(deltaTime);
}


void NormalMonstar::handleWaitingTimer(float deltaTime)
{
	m_turningWaitTimer += deltaTime;
	if (m_turningWaitTimer > 1.f)
	{
		m_isWaitTurning = false;
		m_turningWaitTimer = 0.f;
	}
}

void NormalMonstar::move(sf::Vector2u& windowSize,
						float deltaTime, 
					    const std::list <std::unique_ptr<GameObject>>& foodItems)
{
	if (!m_isWaitTurning)
	{
		if (m_startTimer < START_MAX_TIMER)
		{
			m_startTimer += deltaTime;
			moveRandomly(deltaTime);
		}
		else if(!seekFood(foodItems))
		{
			moveRandomly(deltaTime);
		}
	}

	sf::Vector2f currentPos = m_sprite.getPosition();
	sf::Vector2f newPos = currentPos + m_velocity * deltaTime;
	m_sprite.setPosition(newPos);

	bounceOffWalls(windowSize);
	checkTurn();
}


bool NormalMonstar::tryToEat(GameObject& food)
{
	return food.canBeEatenBy(*this);
}


void NormalMonstar::clicked(int damage, sf::Vector2f mousePos)
{
	SoundManager::getInstance().play("shot");
	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	sf::Vector2f center(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

	m_isWaitTurning = true;
	setHealth(getHealth() - damage);
	if (m_health <= 0)
	{
		SoundManager::getInstance().play("deadBoss");
		EventManager::getInstance().notifyMonstarDeath(center);
		setDestroyed(true);
	}
	m_velocity = sf::Vector2f(-(m_velocity.x), -(m_velocity.y));

	
	sf::Vector2f direction = center - mousePos;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
		direction /= length;

	float knockbackSpeed = 100.f; 
	m_velocity = direction * knockbackSpeed;

	checkTurn();
}

