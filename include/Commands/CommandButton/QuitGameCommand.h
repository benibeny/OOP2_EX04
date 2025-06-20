#pragma once
#include "commands/CommandButton/CommandButton.h"


class QuitGameCommand : public CommandButton 
{
public:
    void execute() override;
};