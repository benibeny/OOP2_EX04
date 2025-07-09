#pragma once
#include "Commands/Command.h"
#include "Screens/HelpScreen.h"

class SwitchBackgroundCommand : public Command
{
public:
    SwitchBackgroundCommand(HelpScreen* screen);
    void execute() override;
private:
    HelpScreen* screen;
};
