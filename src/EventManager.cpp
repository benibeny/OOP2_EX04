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
