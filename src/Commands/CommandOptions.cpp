#include "Commands/CommandOptions.h"


void CommandOptions::execute()
{
	EventManager::getInstance().notifyShowPopUpOption();
}