#include "AquariumManager.h"

int AquariumManager::m_coins = 0;

AquariumManager::AquariumManager(sf::Vector2u windowSize) 
	: m_windowSize(windowSize) 
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
			eatable->clicked(mousePos);
			return;
		}
	}

	if (m_maxFoodSpawned > m_foodCount)
	{
		m_eatables.push_back(std::make_unique<Food>(Food::Foodtype::Worst, mousePos));
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

//maybe a problem
//void AquariumManager::destroyEaten()
//{
//	int foodRemoved = 0;
//
//	auto newEnd = std::remove_if(m_eatables.begin(), m_eatables.end(),
//		[&foodRemoved](const std::unique_ptr<Eatable>& eatable)
//		{
//			if (eatable->isEaten()) 
//			{
//				if (eatable->getType() == Eatable::Type::Food) 
//				{
//					++foodRemoved;
//				}
//				return true;
//			}
//			return false;
//		});
//	m_eatables.erase(newEnd, m_eatables.end());
//	m_foodCount -= foodRemoved;
//}


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
	EventManager& Manager = EventManager::getInstance();

	Manager.subscribeToFoodDestroyed([this]() { m_foodCount--; });

	Manager.subscribeToCreateMoney([this](int type, const sf::Vector2f& position)
		{
			addEatable(std::make_unique<Money>(static_cast<Money::Moneytype>(type), position));
		});
}
