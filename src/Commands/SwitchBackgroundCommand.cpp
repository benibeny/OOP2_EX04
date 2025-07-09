#include "Commands/SwitchBackgroundCommand.h"



SwitchBackgroundCommand::SwitchBackgroundCommand(HelpScreen* screen)
	: screen(screen) 
{}


void SwitchBackgroundCommand::execute()
{
    if (screen) screen->toggleBackground();
}