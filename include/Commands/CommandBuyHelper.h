#pragma once

#include "Command.h"
#include "Entities/GameObject.h"
#include <SFML/Graphics.hpp>
#include "Entities/Goldfish.h"
#include "Entities/HelperJellyfish.h"
#include "Entities/HelperSnail.h"
#include "Game.h"
#include "Managers/EventManager.h"
#include <iostream>
#include <memory>
#include <ctime>
#include <cstdlib>

#define HELPER_NUMBER 2 // Number of helpers to buy

class CommandBuyHelper : public Command
{
public:
	void execute() override;
};