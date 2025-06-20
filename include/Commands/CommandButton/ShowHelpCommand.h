#pragma once
#include "Commands/CommandButton/CommandButton.h"

class ShowHelpCommand : public CommandButton 
{
public:
    void execute() override;
};