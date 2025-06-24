#include "AquariumManager.h"

int AquariumManager::m_coins = 0;

AquariumManager::AquariumManager(sf::Vector2u windowSize) 
	: m_windowSize(windowSize),m_foodType(Food::Foodtype::Worst)
{
	registerToEventManager();
}


void AquariumManager::handleMouseClick(const sf::Vector2f mousePos)
{
	sf::FloatRect mouseBounds(mousePos.x - 5, mousePos.y - 5, 10.f, 10.f);
	for (auto& eatable : m_eatables)
	{
		if (isColliding(mouseBounds, eatable->getBounds()))
		{
			eatable->clicked(m_currentHitDmg);
			return;
		}
	}


	if (!m_monserSpawned && m_maxFoodSpawned > m_foodCount)
	{
		m_eatables.push_back(std::make_unique<Food>(m_foodType, mousePos));
		m_foodCount++;
	}
	
}

void AquariumManager::addEatable(std::unique_ptr<GameObject> eatable)
{
	if (eatable)
	{
		m_eatables.push_back(std::move(eatable));
	}
}


void AquariumManager::update(float deltaTime)
{
	for(auto& eatable : m_eatables)
	{
		if (eatable)
		{
			eatable->update(deltaTime, m_eatables, m_windowSize);
			checkCollisions(eatable);
		}
	}
	checkSpawnMonster(deltaTime);
	destroyEaten();
}


void AquariumManager::draw(sf::RenderWindow& window)
{
	
	for (std::unique_ptr<GameObject>& eatable : m_eatables)
	{
		if (eatable)
		{
			eatable->draw(window);
		}
	}
}




void AquariumManager::destroyEaten()
{
	m_eatables.remove_if([](const std::unique_ptr<GameObject>& eatable)
		{
			return eatable->isDestroyed();
		});
}


void AquariumManager::checkSpawnMonster(float deltaTime)
{

	if (!m_monserSpawned) 
	{
		m_monsterSpawnTimer += deltaTime;
		if (m_monsterSpawnTimer > MONSETER_SPAWN_TIME)
		{
			addEatable(std::make_unique<NormalMonstar>());
			m_monsterSpawnTimer = 0.f;
			m_monserSpawned = true;
		}
		
	}
	
}



void AquariumManager::checkCollisions(std::unique_ptr<GameObject>& eatable)
{
	for(std::unique_ptr<GameObject>& otherEatable : m_eatables)
	{
		if (eatable && otherEatable && eatable != otherEatable && isColliding(eatable->getBounds(), otherEatable->getBounds()))
		{
			processCollision(*eatable, *otherEatable);
		}
	}
}

void AquariumManager::updateFoodType()
{
	if (m_foodType != Food::Foodtype::Best)
	{
		int foodType = int(m_foodType);
		foodType++;
		m_foodType = static_cast<Food::Foodtype>(foodType);
	}
}



bool AquariumManager::isColliding(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
	return rect1.intersects(rect2);
}

//added
int AquariumManager::getCoins() 
{
	return m_coins;
}

void AquariumManager::registerToEventManager()
{
	EventManager& manager = EventManager::getInstance();

	manager.subscribeToFoodAmount([this]()
		{
			m_maxFoodSpawned++;
		});

	manager.subscribeToFoodTier([this]()
		{
			updateFoodType();
		});

	manager.subscribeToBuyAnimal([this](std::unique_ptr<GameObject> gameObj)
		{
			addEatable(std::move(gameObj));
		});

	manager.subscribeToFoodDestroyed([this]() { m_foodCount--; });


	manager.subscribeToCreateMoney([this](int type, const sf::Vector2f& position)
		{
			addEatable(std::make_unique<Money>(static_cast<Money::Moneytype>(type), position));
		});

	manager.subscribeToMonstarDeath([this](const sf::Vector2f& position)
		{
			m_monserSpawned = false;
			addEatable(std::make_unique<Money>(Money::Moneytype::Diamond, position));
		});
}
