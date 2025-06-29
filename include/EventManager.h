#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/GameObject.h"

#include <vector>
#include <functional>
#include <memory>

class EventManager
{
public:
	static EventManager& getInstance();
	

	void subscribeToMoneyChange(const std::function<void(int)> callback);
	void notifyMoneyChange(int amount);
	void unsubscribeFromMoneyChange(const std::function<void(int)>& callback);

	void subscribeToCreateMoney(const std::function<void(int, sf::Vector2f)> callback);
	void notifyCreateMoney(int amount, sf::Vector2f position);
	void unsubscribeFromCreateMoney(const std::function<void(int, sf::Vector2f)>& callback);

	void subscribeToFoodDestroyed(const std::function<void()> callback);
	void notifyFoodDestroyed();
	void unsubscribeFromFoodDestroyed(const std::function<void()>& callback);

	void subscribeToBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)> callback);
	void notifyBuyAnimal(std::unique_ptr<GameObject> animal);
	void unsubscribeFromBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)>& callback);

	void subscribeToFoodTier(const std::function<void()> callback);
	void notifyFoodTier();
	void unsubscribeFromFoodTier(const std::function<void()>& callback);

	void subscribeToFoodAmount(const std::function<void()> callback);
	void notifyFoodAmount();
	void unsubscribeFromFoodAmount(const std::function<void()>& callback);

	void subscribeToBuyWeapon(const std::function<void()> callback);
	void notifyBuyWeapon();
	void unsubscribeFromBuyWeapon(const std::function<void()>& callback);

	void subscribeToMonstarDeath(const std::function<void(sf::Vector2f)> callback);
	void notifyMonstarDeath(sf::Vector2f position);
	void unsubscribeFromMonstarDeath(const std::function<void(sf::Vector2f)>& callback);

	void subscribeToNextLevel(const std::function<void()> callback);
	void notifyNextLevel();
	void unsubscribeFromNextLevel(const std::function<void()>& callback);


	void cleanUp();

private:
	EventManager() = default;
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;
	~EventManager() = default;

	//events : moneyclick, createmoney, fooddestoryed
	std::vector<std::function<void(int)>> m_moneyChange;
	std::vector<std::function<void(int,sf::Vector2f)>> m_createMoney;
	std::vector<std::function<void()>> m_foodDestroyed;

	//m_buyAnimalCallBack only one only aquariummanager use it
	std::function<void(std::unique_ptr<GameObject>)> m_buyAnimalCallBack;
	std::vector<std::function<void()>> m_foodTier;
	std::vector<std::function<void()>> m_foodAmount;
	std::vector<std::function<void()>> m_buyWeapon;
	std::vector<std::function<void(sf::Vector2f)>> m_monstarDeath;
	std::vector<std::function<void()>> m_nextLevel;

};