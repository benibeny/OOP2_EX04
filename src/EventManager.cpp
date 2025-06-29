#include "EventManager.h"



EventManager& EventManager::getInstance()
{
	static EventManager instance;
	return instance;
}


void EventManager::cleanUp()
{
	m_createMoney.clear();
	m_moneyChange.clear();
	m_foodDestroyed.clear();
	m_foodTier.clear();
	m_foodAmount.clear();
	m_buyWeapon.clear();
	m_monstarDeath.clear();
	m_nextLevel.clear();
	m_buyAnimalCallBack = nullptr;

}

void EventManager::subscribeToMoneyChange(const std::function<void(int)> callback)
{
	m_moneyChange.push_back(callback);
}

void EventManager::notifyMoneyChange(int amount)
{
	for (auto& callback : m_moneyChange)
	{
		callback(amount);
	}
}

void EventManager::unsubscribeFromMoneyChange(const std::function<void(int)>& callback)
{
	auto it = std::find_if(m_moneyChange.begin(), m_moneyChange.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});

	if (it != m_moneyChange.end())
	{
		m_moneyChange.erase(it);
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

void EventManager::unsubscribeFromCreateMoney(const std::function<void(int, sf::Vector2f)>& callback)
{
	auto it = std::find_if(m_createMoney.begin(), m_createMoney.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});

	if (it != m_createMoney.end())
	{
		m_createMoney.erase(it);
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

void EventManager::unsubscribeFromFoodDestroyed(const std::function<void()>& callback)
{
	auto it = std::find_if(m_foodDestroyed.begin(), m_foodDestroyed.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});
	if (it != m_foodDestroyed.end())
	{
		m_foodDestroyed.erase(it);
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

void EventManager::unsubscribeFromBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)>& callback)
{
	m_buyAnimalCallBack = nullptr;
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

void EventManager::unsubscribeFromFoodTier(const std::function<void()>& callback)
{
	auto it = std::find_if(m_foodTier.begin(), m_foodTier.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});
	if (it != m_foodTier.end())
	{
		m_foodTier.erase(it);
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

void EventManager::unsubscribeFromFoodAmount(const std::function<void()>& callback)
{
	auto it = std::find_if(m_foodAmount.begin(), m_foodAmount.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});
	if (it != m_foodAmount.end())
	{
		m_foodAmount.erase(it);
	}
}


void EventManager::subscribeToBuyWeapon(const std::function<void()> callback)
{
	m_buyWeapon.push_back(callback);
}

void EventManager::notifyBuyWeapon()
{
	for(auto callback : m_buyWeapon)
		if (callback)
		{
			callback();
		}
}

void EventManager::unsubscribeFromBuyWeapon(const std::function<void()>& callback)
{
	auto it = std::find_if(m_buyWeapon.begin(), m_buyWeapon.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});
	if (it != m_buyWeapon.end())
	{
		m_buyWeapon.erase(it);
	}
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

void EventManager::unsubscribeFromMonstarDeath(const std::function<void(sf::Vector2f)>& callback)
{
	auto it = std::find_if(m_monstarDeath.begin(), m_monstarDeath.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});
	if (it != m_monstarDeath.end())
	{
		m_monstarDeath.erase(it);
	}
}

void EventManager::subscribeToNextLevel(const std::function<void()> callback)
{
	m_nextLevel.push_back(callback);
}

void EventManager::notifyNextLevel()
{
	for (auto& callback : m_nextLevel)
	{
		if (callback)
		{
			callback();
		}
	}
}

void EventManager::unsubscribeFromNextLevel(const std::function<void()>& callback)
{
	auto it = std::find_if(m_nextLevel.begin(), m_nextLevel.end(), [&callback](const auto& func)
		{
			return func.target_type() == callback.target_type();
		});
	if (it != m_nextLevel.end())
	{
		m_nextLevel.erase(it);
	}
}
