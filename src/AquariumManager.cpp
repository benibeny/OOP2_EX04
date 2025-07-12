#include "AquariumManager.h"


AquariumManager::AquariumManager(int currentLevel)
	:m_foodType(Food::Foodtype::Worst), m_currentLevel(currentLevel)
{
	ResourceManager& resourceManager = ResourceManager::getInstance();
	resourceManager.loadSpriteSheet(NORMALMONSTAR_HITMARK_SPTITE, 1, 11);
	resourceManager.setSpriteTextureFromSheet(m_hitMark, NORMALMONSTAR_HITMARK_SPTITE, 0, 0);

	createGoldFishStart();
}


void AquariumManager::createGoldFishStart()
{
	sf::Vector2u windowSize = Game::getInstance().getWindow().getSize();

	addEatable(GameObjectFactory::getInstance().create("GoldFish", {500.0f, 500.0f}));
	addEatable(GameObjectFactory::getInstance().create("GoldFish", { 500.0f, 500.0f }));
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
			std::string foodTypeStr; 
			switch (m_foodType) {
			case Food::Foodtype::Worst:  foodTypeStr = "Food_Worst"; break;
			case Food::Foodtype::Medium: foodTypeStr = "Food_Medium"; break;
			case Food::Foodtype::Best:   foodTypeStr = "Food_Best"; break;
			}
			m_eatables.push_back(GameObjectFactory::getInstance().create(foodTypeStr, mousePos));

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
	sf::Vector2u windowSize = Game::getInstance().getWindow().getSize();

	for(auto& eatable : m_eatables)
	{
		if (eatable)
		{
			eatable->update(deltaTime, m_eatables, windowSize);
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

	//check if lost game
	int currntAnimals = m_eatables.size();
	currntAnimals -= m_foodCount;
	if (m_monserSpawned)
	{
		currntAnimals--;
	}
	if (currntAnimals <= 0)
	{
		ScreenManager::getInstance().switchScreen(ScreenType::GameOver);
		EventManager::getInstance().notifyGameOver();
		
	}

}


void AquariumManager::checkSpawnMonsterAndHit(float deltaTime)
{

	if (!m_monserSpawned) 
	{
		m_monsterSpawnTimer += deltaTime;
		if (m_monsterSpawnTimer > MONSETER_SPAWN_TIME)
		{
			if (m_currentLevel > 2)
			{
				addEatable(std::make_unique<SquidMonstar>());
			}
			else 
			{
				addEatable(GameObjectFactory::getInstance().create("NormalMonstar", { 300.0f, 300.0f })); 
			}
			
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
			std::string moneyTypeStr;
			switch (static_cast<Money::Moneytype>(type)) {
			case Money::Moneytype::Silver:  moneyTypeStr = "Money_Silver"; break;
			case Money::Moneytype::Gold:    moneyTypeStr = "Money_Gold"; break;
			case Money::Moneytype::Diamond: moneyTypeStr = "Money_Diamond"; break;
			}
			addEatable(GameObjectFactory::getInstance().create(moneyTypeStr, position));

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

			addEatable(GameObjectFactory::getInstance().create("Money_Diamond", position));
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

	createGoldFishStart();


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