#pragma once

#include <iostream>
#include <memory>

#include "Command.h"
#include "Entities/Pirana.h"
#include "Entities/GameObject.h"

#include <SFML/Graphics.hpp>
#include "EventManager.h"


class CommandBuyPirana : public Command
{
	void execute() override;
};