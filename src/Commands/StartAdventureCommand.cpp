#include "Commands/StartAdventureCommand.h"
#include "Screens/GameScreen.h"
#include "ScreenManager.h"
#include "Game.h"

#include <iostream>

void StartAdventureCommand::execute() 
{
    ScreenManager::getInstance().switchScreen(ScreenType::GameScreen);
}

