#pragma once
#include <typeinfo> 
#include <typeindex>
#include <unordered_map>
#include <string>

#include "Entities/GameObject.h"
#include "Entities/GoldFish.h"
#include "Entities/Food.h"


void processCollision(GameObject& a, GameObject& b);
