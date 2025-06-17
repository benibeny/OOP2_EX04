#pragma once
#include <typeinfo> 
#include <typeindex>
#include <unordered_map>
#include <string>

#include "Entities/Eatable.h"
#include "Entities/GoldFish.h"
#include "Entities/Food.h"


// Sample struct for exception throwing
//struct UnknownCollision : public std::runtime_error
//{
//    UnknownCollision(Eatable& a, Eatable& b)
//        : std::runtime_error(std::string("Unknown collision"))
//    {
//    }
//};


void processCollision(Eatable& a, Eatable& b);
