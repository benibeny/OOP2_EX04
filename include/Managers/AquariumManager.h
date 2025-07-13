#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>

#include "Entities/Fish.h"
#include "Entities/Food.h"
#include "Entities/NormalMonstar.h"
#include "Entities/HelperJellyfish.h"
#include "Entities/SquidMonstar.h"
#include "GameObjectFactory.h"
#include "CollisionHandler.h"
#include "Managers/EventManager.h"
#include "Managers/ScreenManager.h"
#include "Game.h"

#define MONSETER_SPAWN_TIME 12.0f // Time in seconds to spawn a monster
#define NORMALMONSTAR_HITMARK_SPTITE "hitmark.png"


class AquariumManager
{
public:
	AquariumManager(int currentLevel);
	
	void handleMouseClick(const sf::Vector2f mousePos);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void reset();

	void registerToEventManager();
	void unRegisterFromEventManager();
private:
	void addEatable(std::unique_ptr<GameObject> eatable);
	void createGoldFishStart();
	bool isColliding(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
	void destroyEaten();
	void checkSpawnMonsterAndHit(float deltaTime);
	void checkCollisions(std::unique_ptr<GameObject>& eatable);
	void updateFoodType();


	std::list<std::unique_ptr<GameObject>> m_eatables;

	int m_maxFoodSpawned = 1;
	int m_foodCount = 0;
	Food::Foodtype m_foodType;

	bool m_monserSpawned = false;
	float m_monsterSpawnTimer = 0.0f;
	int m_currentHitDmg = 5;

	int m_currentLevel;

	int m_weaponLevel = 0;
	float m_hitAnimationTimer = 0.0f;
	bool m_isHitAnimation = false;
	sf::Sprite m_hitMark;

	//vector to do unsubscribe from events
	struct EventSubscription
	{
		std::function<void()> unsubscribe;
	};
	std::vector<EventSubscription> m_eventSubscriptions;
};