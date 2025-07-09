#pragma once
#include "Commands/Command.h"
#include "SoundManager.h"
#include "MusicManager.h"

class ToggleMuteCommand : public Command {
public:
    void execute() override;
};
