#include "EventManager.h"



EventManager& EventManager::getInstance()
{
	static EventManager instance;
	return instance;
}


void EventManager::cleanUp()
{
	m_createMoney.clear();
	m_moneyClick.clear();
	m_foodDestroyed.clear();
	m_foodTier.clear();
	m_foodAmount.clear();
	m_buyWeapon.clear();
	m_monstarDeath.clear();
	m_buyAnimalCallBack = nullptr;

}

void EventManager::subscribeToMoneyClick(const std::function<void(int)> callback)
{
	m_moneyClick.push_back(callback);
}

void EventManager::notifyMoneyClick(int amount)
{
	for (auto& callback : m_moneyClick)
	{
		callback(amount);
	}
}

void EventManager::subscribeToCreateMoney(const std::function<void(int, sf::Vector2f)> callback)
{
	m_createMoney.push_back(callback);
}

void EventManager::notifyCreateMoney(int amount, sf::Vector2f position)
{
	for (auto& callback : m_createMoney)
	{
		callback(amount, position);
	}
}


void EventManager::subscribeToFoodDestroyed(const std::function<void()> callback)
{
	m_foodDestroyed.push_back(callback);
}

void EventManager::notifyFoodDestroyed()
{
	for (auto& callback : m_foodDestroyed)
	{
		if (callback)
		{
			callback();
		}
		
	}
}


void EventManager::subscribeToBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)> callback)
{
	m_buyAnimalCallBack = callback;
}

void EventManager::notifyBuyAnimal(std::unique_ptr<GameObject> animal)
{
	if (m_buyAnimalCallBack)
	{
		m_buyAnimalCallBack(std::move(animal));
	}
	
}


void EventManager::subscribeToFoodTier(const std::function<void()> callback)
{
	m_foodTier.push_back(callback);
}

void EventManager::notifyFoodTier()
{
	for (auto& callback : m_foodTier)
	{
		if (callback)
		{
			callback();
		}
	}
}


void EventManager::subscribeToFoodAmount(const std::function<void()> callback)
{
	m_foodAmount.push_back(callback);
}

void EventManager::notifyFoodAmount()
{
	for (auto& callback : m_foodAmount)
	{
		if (callback)
		{
			callback();
		}
	}
}


void EventManager::subscribeToBuyWeapon(const std::function<void()> callback)
{
}

void EventManager::notifyBuyWeapon()
{
}


void EventManager::subscribeToMonstarDeath(const std::function<void(sf::Vector2f )> callback)
{
	m_monstarDeath.push_back(callback);
}

void EventManager::notifyMonstarDeath(sf::Vector2f position)
{
	for (auto& callback : m_monstarDeath)
	{
		if (callback)
		{
			callback(position);
		}
	}
}
