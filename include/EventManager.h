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
	

	void subscribeToMoneyClick(const std::function<void(int)> callback);
	void notifyMoneyClick(int amount);

	void subscribeToCreateMoney(const std::function<void(int, sf::Vector2f)> callback);
	void notifyCreateMoney(int amount, sf::Vector2f position);

	void subscribeToFoodDestroyed(const std::function<void()> callback);
	void notifyFoodDestroyed();

	void subscribeToBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)> callback);
	void notifyBuyAnimal(std::unique_ptr<GameObject> animal);

	void subscribeToFoodTier(const std::function<void()> callback);
	void notifyFoodTier();

	void subscribeToFoodAmount(const std::function<void()> callback);
	void notifyFoodAmount();

	void subscribeToBuyWeapon(const std::function<void()> callback);
	void notifyBuyWeapon();

	void subscribeToMonstarDeath(const std::function<void(sf::Vector2f)> callback);
	void notifyMonstarDeath(sf::Vector2f position);


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

	//m_buyAnimalCallBack only one only aquariummanager use it
	std::function<void(std::unique_ptr<GameObject>)> m_buyAnimalCallBack;
	std::vector<std::function<void()>> m_foodTier;
	std::vector<std::function<void()>> m_foodAmount;
	std::vector<std::function<void()>> m_buyWeapon;
	std::vector<std::function<void(sf::Vector2f)>> m_monstarDeath;

};