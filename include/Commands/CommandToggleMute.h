#pragma once
#include "Commands/Command.h"
#include "Managers/SoundManager.h"
#include "Managers/MusicManager.h"

class ToggleMuteCommand : public Command {
public:
    void execute() override;
};
