#include "Entities/NormalMonstar.h"

NormalMonstar::NormalMonstar()
	:Animal(Type::Monster,sf::Vector2f(700.0f,400.0f), NORMALMONSTAR_SPEED, NORMALMONSTAR_SPRITE,2,10,0),m_startTimer(0.0f)
{
	m_health = 100;
	m_sprite.setScale(1.5f,1.5f);

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
	setPosition(newPos);

	bounceOffWalls(windowSize);
	checkTurn();
}


bool NormalMonstar::seekFood(const std::list<std::unique_ptr<GameObject>>& foodItems)
{
	bool foundFood = false;
	//pointer to pointer to avoid copying the vector
	std::vector<GameObject*> filteredFood;

	for (const auto& foodItem : foodItems)
	{
		if (foodItem && !foodItem->isDestroyed() && foodItem->getType() == Type::GoldFish)
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

GameObject* NormalMonstar::findClosestFood(const std::vector<GameObject*> foodItems)
{
	if (foodItems.empty())
	{
		return nullptr;
	}

	GameObject* closestFood = nullptr;
	float closestDistance = std::numeric_limits<float>::max();
	sf::Vector2f fishCenter = getCenter();

	for (GameObject* foodItem : foodItems)
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

void NormalMonstar::moveTowardFood(const GameObject* food)
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


void NormalMonstar::clicked(int damage, sf::Vector2f mousePos)
{
	m_isWaitTurning = true;
	setHealth(getHealth() - damage);
	if (m_health <= 0)
	{
		setDestroyed(true);
		EventManager::getInstance().notifyMonstarDeath(m_sprite.getPosition());
	}
	m_velocity = sf::Vector2f(-(m_velocity.x), -(m_velocity.y));

	sf::FloatRect bounds = m_sprite.getGlobalBounds();
	sf::Vector2f center(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);



	sf::Vector2f direction = center - mousePos;

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
		direction /= length;

	float knockbackSpeed = 100.f; 
	m_velocity = direction * knockbackSpeed;

	checkTurn();
}