#pragma once
#include "Commands/CommandButton/CommandButton.h"

class StartAdventureCommand : public CommandButton 
{
public:
    void execute() override;
};