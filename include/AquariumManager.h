#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "Entities/Fish.h"
#include "Entities/Food.h"
#include "Entities/NormalMonstar.h"
#include "CollisionHandler.h"
#include "EventManager.h"

#define MONSETER_SPAWN_TIME 1.0f // Time in seconds to spawn a monster

class AquariumManager
{
public:
	AquariumManager(sf::Vector2u windowSize);
	

	void handleMouseClick(const sf::Vector2f mousePos);
	void addEatable(std::unique_ptr<GameObject> eatable);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	//added
	static int getCoins(); // Add this line to the public section

	void registerToEventManager();

private:
	bool isColliding(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
	void destroyEaten();
	void checkSpawnMonster(float deltaTime);
	void checkCollisions(std::unique_ptr<GameObject>& eatable);
	void updateFoodType();
	//all with things out money
	std::list<std::unique_ptr<GameObject>> m_eatables;


	static int m_coins;

	int m_maxFoodSpawned = 1;
	int m_foodCount = 0;
	Food::Foodtype m_foodType;

	bool m_monserSpawned = false;
	float m_monsterSpawnTimer = 0.0f;

	int m_currentHitDmg = 5;

	sf::Vector2u m_windowSize;
};