#include "Commands/QuitGameCommand.h"
#include <iostream>
#include "Game.h"


void QuitGameCommand::execute() 
{
    Game::getInstance().quit();
}