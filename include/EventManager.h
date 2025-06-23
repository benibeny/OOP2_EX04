#pragma once
#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>

class EventManager
{
public:
	static EventManager& getInstance();
	

	void subscribeToMoneyClick(const std::function<void(int)> callback);
	void notifyMoneyClick(int amount);

	void subscribeToCreateMoney(const std::function<void(int, sf::Vector2f)> callback);
	void notifyCreateMoney(int amount, sf::Vector2f position);

	void subscribeToFoodDestroyed(const std::function<void()> callback);
	void notifyFoodDestroyed();
	void cleanUp();

private:
	EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;
	~EventManager() = default;

	//events : moneyclick, createmoney, fooddestoryed
	std::vector<std::function<void(int)>> m_moneyClick;
	std::vector<std::function<void(int,sf::Vector2f)>> m_createMoney;
	std::vector<std::function<void()>> m_foodDestroyed;

};