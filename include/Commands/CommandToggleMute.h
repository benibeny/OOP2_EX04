#pragma once
#include "Commands/Command.h"
#include "SoundManager.h"
#include "MusicManager.h"

class ToggleMuteCommand : public Command {
public:
    void execute() override {
        bool muted = !SoundManager::getInstance().isMuted();
        SoundManager::getInstance().setMuted(muted);
        MusicManager::getInstance().setMuted(muted);

        if (muted)
            std::cout << "Muted all sounds and music\n";
        else
            std::cout << "Unmuted sounds and music\n";
    }
};
