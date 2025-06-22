#pragma once
#include "Command.h"

class StartAdventureCommand : public Command 
{
public:
    void execute() override;
};