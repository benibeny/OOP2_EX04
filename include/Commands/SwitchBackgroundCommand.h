//add
#pragma once
#include "Commands/Command.h"
#include "Screens/HelpScreen.h"

class SwitchBackgroundCommand : public Command {
public:
    SwitchBackgroundCommand(HelpScreen* screen) : screen(screen) {}
    void execute() override {
        if (screen) screen->toggleBackground();
    }
private:
    HelpScreen* screen;
};
