#include "Commands/CommandToggleMute.h"



void ToggleMuteCommand::execute()
{
    bool muted = !SoundManager::getInstance().isMuted();
    SoundManager::getInstance().setMuted(muted);
    MusicManager::getInstance().setMuted(muted);
}