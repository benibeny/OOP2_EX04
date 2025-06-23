#include "CollisionHandler.h"


#include "Entities/GameObject.h"
#include "Entities/GoldFish.h"
#include "Entities/Food.h"

#include <iostream>
namespace 
{

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



	using CollisionHandlerFunction = void(*)(GameObject& , GameObject&);
	
	using CollisionPairKey = std::pair<std::type_index, std::type_index>;

	using CollisionHandlerMap = std::map<CollisionPairKey, CollisionHandlerFunction>;


	CollisionHandlerMap initializeCollisionMap() 
	{
		CollisionHandlerMap collisionMap;
		
		collisionMap[CollisionPairKey(typeid(GoldFish), typeid(Food))] = &goldFishFood;
		collisionMap[CollisionPairKey(typeid(Food), typeid(GoldFish))] = &foodGoldFish;

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