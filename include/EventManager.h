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
	
	//when buying something, and pickup money
	void subscribeToMoneyChange(const std::function<void(int)> callback);
	void notifyMoneyChange(int amount);
	void unsubscribeFromMoneyChange(const std::function<void(int)>& callback);

	//acurium manager use it when fish create money
	void subscribeToCreateMoney(const std::function<void(int, sf::Vector2f)> callback);
	void notifyCreateMoney(int amount, sf::Vector2f position);
	void unsubscribeFromCreateMoney(const std::function<void(int, sf::Vector2f)>& callback);

	//when food is destroyed, notify all subscribers
	void subscribeToFoodDestroyed(const std::function<void()> callback);
	void notifyFoodDestroyed();
	void unsubscribeFromFoodDestroyed(const std::function<void()>& callback);

	//every time buy animal in shop ,or when need to spawn an animal
	void subscribeToBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)> callback);
	void notifyBuyAnimal(std::unique_ptr<GameObject> animal);
	void unsubscribeFromBuyAnimal(const std::function<void(std::unique_ptr<GameObject>)>& callback);

	//when food tier is bought, notify aquarium manager
	void subscribeToFoodTier(const std::function<void()> callback);
	void notifyFoodTier();
	void unsubscribeFromFoodTier(const std::function<void()>& callback);

	//when food amount is bought, notify aquarium manager
	void subscribeToFoodAmount(const std::function<void()> callback);
	void notifyFoodAmount();
	void unsubscribeFromFoodAmount(const std::function<void()>& callback);

	//when weapon is bought, notify aquarium manager
	void subscribeToBuyWeapon(const std::function<void()> callback);
	void notifyBuyWeapon();
	void unsubscribeFromBuyWeapon(const std::function<void()>& callback);

	//when monstar is killed, notify aquarium manager no change mouse click and create money
	void subscribeToMonstarDeath(const std::function<void(sf::Vector2f)> callback);
	void notifyMonstarDeath(sf::Vector2f position);
	void unsubscribeFromMonstarDeath(const std::function<void(sf::Vector2f)>& callback);

	//when next level is reached, notify chose level screen 
	void subscribeToNextLevel(const std::function<void(int nextLevel)> callback);
	void notifyNextLevel(int nextLevel);
	void unsubscribeFromNextLevel(const std::function<void(int nextLevel)>& callback);

	//shopbar subscribe and aquarium manager notify it when try to buy food
	void subscribeToTryBuyFood(const std::function<bool()> callback);
	bool notifyTryBuyFood();
	void unsubscribeFromTryBuyFood();

	//shopbar menu button tell the gamescreen
	void subscribeToShowPopUpOption(const std::function<void()> callback);
	void notifyShowPopUpOption();
	void unsubscribeFromShowPopUpOption();

	//when all the fish die
	void subscribeToGameOver(const std::function<void()> callback);
	void notifyGameOver();
	void unsubscribeFromGameOver(const std::function<void()>& callback);


	//clean up all events,reset all callbacks
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
	std::vector<std::function<void(int nextLevel)>> m_nextLevel;
	std::function<void()> m_gameOver;

	std::function<bool()> m_tryBuyFoodCallBack;
	std::function<void()> m_showPopUpOption;

};