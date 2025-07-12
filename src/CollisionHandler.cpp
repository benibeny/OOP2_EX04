#include "CollisionHandler.h"


#include "Entities/GameObject.h"
#include "Entities/GoldFish.h"
#include "Entities/Food.h"
#include "Entities/NormalMonstar.h"
#include "Entities/Pirana.h"
#include "Entities/HelperJellyfish.h"
#include "Entities/HelperSnail.h"
#include "Entities/Money.h"
#include "Entities/SquidMonstar.h"
#include "Managers/SoundManager.h"

#include <iostream>
namespace 
{
	void normalMonstarAnimal(GameObject& normalMonstar, GameObject& animalToDestroy)
	{
		animalToDestroy.setDestroyed(true);
		SoundManager::getInstance().play("alienEat");
	}

	void animalNormalMonstar(GameObject& animalToDestroy, GameObject& normalMonstar)
	{
		normalMonstarAnimal(normalMonstar, animalToDestroy);
	}

	void goldFishFood(GameObject& goldFish, GameObject& food)
	{
		GoldFish& goldFishFound = static_cast<GoldFish&>(goldFish);
		Food& FoodFound = static_cast<Food&>(food);
		if (goldFishFound.isHungry())
		{
			goldFishFound.foodEatenIncrement(FoodFound.foodEaten());
		}
	}

	void foodGoldFish(GameObject& food, GameObject& goldFish)
	{
		goldFishFood(goldFish, food);
	}

	

	void piranaGoldFish(GameObject& pirana, GameObject& goldFish)
	{
		Pirana& piranaFound = static_cast<Pirana&>(pirana);
		if (piranaFound.isHungry())
		{
			piranaFound.foodEatenIncrement();
			goldFish.setDestroyed(true);
		}
		
	}

	void goldFishPirana(GameObject& goldFish, GameObject& pirana)
	{
		piranaGoldFish(pirana, goldFish);
	}

	void helperMoney(GameObject& helper, GameObject& money)
	{
		Money& moneyFound = static_cast<Money&>(money);
		moneyFound.clicked();
	}

	void moneyHelper(GameObject& money, GameObject& helper)
	{
		helperMoney(helper, money);
	}


	using CollisionHandlerFunction = void(*)(GameObject& , GameObject&);
	
	using CollisionPairKey = std::pair<std::type_index, std::type_index>;

	using CollisionHandlerMap = std::map<CollisionPairKey, CollisionHandlerFunction>;


	CollisionHandlerMap initializeCollisionMap() 
	{
		CollisionHandlerMap collisionMap;
		
		collisionMap[CollisionPairKey(typeid(GoldFish), typeid(Food))] = &goldFishFood;
		collisionMap[CollisionPairKey(typeid(Food), typeid(GoldFish))] = &foodGoldFish;
		collisionMap[CollisionPairKey(typeid(NormalMonstar), typeid(GoldFish))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(GoldFish), typeid(NormalMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(NormalMonstar), typeid(Pirana))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(Pirana), typeid(NormalMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(Pirana), typeid(GoldFish))] = &piranaGoldFish;
		collisionMap[CollisionPairKey(typeid(GoldFish), typeid(Pirana))] = &goldFishPirana;
		collisionMap[CollisionPairKey(typeid(NormalMonstar), typeid(HelperJellyfish))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(HelperJellyfish), typeid(NormalMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(HelperJellyfish), typeid(Money))] = &helperMoney;
		collisionMap[CollisionPairKey(typeid(Money), typeid(HelperJellyfish))] = &moneyHelper;

		collisionMap[CollisionPairKey(typeid(NormalMonstar), typeid(HelperSnail))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(HelperSnail), typeid(NormalMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(HelperSnail), typeid(Money))] = &helperMoney;
		collisionMap[CollisionPairKey(typeid(Money), typeid(HelperSnail))] = &moneyHelper;


		collisionMap[CollisionPairKey(typeid(SquidMonstar), typeid(GoldFish))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(SquidMonstar), typeid(Pirana))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(SquidMonstar), typeid(HelperJellyfish))] = &normalMonstarAnimal;
		collisionMap[CollisionPairKey(typeid(SquidMonstar), typeid(HelperSnail))] = &normalMonstarAnimal;

		collisionMap[CollisionPairKey(typeid(GoldFish), typeid(SquidMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(Pirana), typeid(SquidMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(HelperJellyfish), typeid(SquidMonstar))] = &animalNormalMonstar;
		collisionMap[CollisionPairKey(typeid(HelperSnail), typeid(SquidMonstar))] = &animalNormalMonstar;
		




		return collisionMap;
	}



	CollisionHandlerFunction lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static CollisionHandlerMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}
}


void processCollision(GameObject& object1, GameObject& object2)
{
	auto collisionFunction = lookup(typeid(object1), typeid(object2));
	if (collisionFunction)
	{
		collisionFunction(object1, object2);
	}
	
}