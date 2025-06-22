#pragma once
#include "Command.h"


class QuitGameCommand : public Command 
{
public:
    void execute() override;
};