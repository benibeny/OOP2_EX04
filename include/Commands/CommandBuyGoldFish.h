#pragma once

#include "Command.h"
#include "Entities/GameObject.h"
#include <SFML/Graphics.hpp>
#include "Entities/Goldfish.h"
#include "Game.h"
#include "EventManager.h"
#include <iostream>
#include <memory>

class CommandBuyGoldFish : public Command
{
public:
	void execute() override;
};