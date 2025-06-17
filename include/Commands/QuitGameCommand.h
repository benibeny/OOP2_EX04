#pragma once
#include "commands/Command.h"


class QuitGameCommand : public Command 
{
public:
    void execute() override;
};