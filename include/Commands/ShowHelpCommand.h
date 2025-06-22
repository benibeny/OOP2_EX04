#pragma once
#include "Command.h"

class ShowHelpCommand : public Command 
{
public:
    void execute() override;
};