#include "AquariumManager.h"

AquariumManager::AquariumManager(sf::Vector2u windowSize) 
	: m_windowSize(windowSize),m_foodType(Food::Foodtype::Worst)
{
	//registerToEventManager();

	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.loadSpriteSheet(NORMALMONSTAR_HITMARK_SPTITE, 1, 11);
	resourceManager.setSpriteTextureFromSheet(m_hitMark, NORMALMONSTAR_HITMARK_SPTITE, 0, 0);
}


void AquariumManager::handleMouseClick(const sf::Vector2f mousePos)
{
	bool clickedOnGameObject = false;
	sf::FloatRect mouseBounds(mousePos.x - 5, mousePos.y - 5, 10.f, 10.f);
	for (auto& eatable : m_eatables)
	{
		if (isColliding(mouseBounds, eatable->getBounds()))
		{
			eatable->clicked(m_currentHitDmg, mousePos);
			clickedOnGameObject = true;
		}
	}

	if (!m_monserSpawned)
	{
		if (m_maxFoodSpawned > m_foodCount && !clickedOnGameObject && EventManager::getInstance().notifyTryBuyFood())
		{
			m_eatables.push_back(std::make_unique<Food>(m_foodType, mousePos));
			m_foodCount++;
		}

	}
	else 
	{
		ResourceManager::getInstance().setSpriteTextureFromSheet(m_hitMark, NORMALMONSTAR_HITMARK_SPTITE, 0, m_weaponLevel);

		m_hitMark.setOrigin(m_hitMark.getLocalBounds().width / 2.0f, m_hitMark.getLocalBounds().height / 2.0f);
		m_hitMark.setScale(0.2f, 0.2f);
		m_hitMark.setPosition(mousePos);
		m_isHitAnimation = true;
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
	checkSpawnMonsterAndHit(deltaTime);
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

	if (m_isHitAnimation)
	{
		window.draw(m_hitMark);
	}
}




void AquariumManager::destroyEaten()
{
	m_eatables.remove_if([](const std::unique_ptr<GameObject>& eatable)
		{
			return eatable->isDestroyed();
		});
}


void AquariumManager::checkSpawnMonsterAndHit(float deltaTime)
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
	else if(m_isHitAnimation)
	{
		m_hitAnimationTimer += deltaTime;

		if (m_hitAnimationTimer > 1.f)
		{
			m_isHitAnimation = false;
			m_hitAnimationTimer = 0.f;
			m_hitMark.setScale(0.f,0.f);
		}
		sf::Vector2f currScale = m_hitMark.getScale();
		m_hitMark.setScale(currScale.x / 1.1f, currScale.y / 1.1f);
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



void AquariumManager::registerToEventManager()
{
	EventManager& manager = EventManager::getInstance();

	auto amountFoodCallBack = [this]()
		{
			m_maxFoodSpawned++;
		};
	manager.subscribeToFoodAmount(amountFoodCallBack);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromFoodAmount(amountFoodCallBack); }
		});


	auto FoodTierCallBack = [this]()
		{
			updateFoodType();
		};
	manager.subscribeToFoodTier(FoodTierCallBack);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromFoodTier(FoodTierCallBack); }
		});


	auto BuyAnimalCallBack = [this](std::unique_ptr<GameObject> gameObj)
		{
			addEatable(std::move(gameObj));
		};
	manager.subscribeToBuyAnimal(BuyAnimalCallBack);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromBuyAnimal(BuyAnimalCallBack); }
		});

	

	auto FoodDestroyed = [this]()
		{
			m_foodCount--;
		};
	manager.subscribeToFoodDestroyed(FoodDestroyed);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromFoodDestroyed(FoodDestroyed); }
		});


	auto CreateMoney = [this](int type, const sf::Vector2f& position)
		{
			addEatable(std::make_unique<Money>(static_cast<Money::Moneytype>(type), position));
		};
	manager.subscribeToCreateMoney(CreateMoney);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromCreateMoney(CreateMoney); }
		});


	auto MonstarDeath = [this](const sf::Vector2f& position)
		{
			m_monserSpawned = false;
			m_isHitAnimation = false;
			m_hitAnimationTimer = 0.f;
			m_hitMark.setScale(0.f, 0.f);

			addEatable(std::make_unique<Money>(Money::Moneytype::Diamond, position));
		};
	manager.subscribeToMonstarDeath(MonstarDeath);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.unsubscribeFromMonstarDeath(MonstarDeath); }
		});


	

	auto BuyWeapon = [this]()
		{
			m_currentHitDmg += 5;

			if (m_weaponLevel < 11)
			{
				m_weaponLevel++;
			}
		};
	manager.subscribeToBuyWeapon(BuyWeapon);
	m_eventSubscriptions.push_back(
		{
			[=,&manager]() {manager.subscribeToBuyWeapon(BuyWeapon); }
		});

}

void AquariumManager::unRegisterFromEventManager()
{
	for(auto& subscription : m_eventSubscriptions)
	{
		subscription.unsubscribe();
	}
	m_eventSubscriptions.clear();
}


void AquariumManager::reset()
{
	m_eatables.clear();

	addEatable(std::make_unique<GoldFish>(sf::Vector2f(500.0f,500.0f)));
	addEatable(std::make_unique<GoldFish>(sf::Vector2f(400.0f, 400.0f)));

	m_maxFoodSpawned = 1;
	m_foodCount = 0;
	m_foodType = Food::Foodtype::Worst;

	m_monserSpawned = false;
	m_monsterSpawnTimer = 0.0f;

	m_currentHitDmg = 5;
	m_weaponLevel = 0;
	m_hitAnimationTimer = 0.0f;
	m_isHitAnimation = false;

	m_hitMark.setScale(0.f, 0.f);
}