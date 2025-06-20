#include "Commands/CommandButton/ShowHelpCommand.h"
#include <iostream>
#include "Screens/HelpScreen.h"
#include "ScreenManager.h"
#include "Game.h"

void ShowHelpCommand::execute() 
{
    ScreenManager::getInstance().switchScreen(new HelpScreen());
}