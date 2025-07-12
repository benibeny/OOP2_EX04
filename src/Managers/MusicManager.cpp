#include "Managers/MusicManager.h"
#include <stdexcept>

MusicManager& MusicManager::getInstance() {
    static MusicManager instance;
    return instance;
}

void MusicManager::loadTrack(const std::string& key, const std::string& filePath) {
    auto music = std::make_unique<sf::Music>();
    if (!music->openFromFile(filePath)) {
        throw std::runtime_error("Failed to open music file: " + filePath);
    }

    m_tracks[key] = std::move(music);

}

void MusicManager::play(const std::string& key, bool loop) 
{
    if (m_muted)
        return;

    stopCurrent();
    

    auto it = m_tracks.find(key);
    if (it == m_tracks.end()) {
        loadTrack(key, key); // fallback: try to load using the key as file path
        it = m_tracks.find(key);
    }

    m_currentTrack = it->second.get();
    m_currentTrack->setLoop(loop);
    m_lastTrackKey = key;
    m_lastLoopState = loop;

    m_currentTrack->setVolume(30); 
    m_currentTrack->play();
}

void MusicManager::stopCurrent() {
    if (m_currentTrack) {
        m_currentTrack->stop();
        m_currentTrack = nullptr;
    }
}

void MusicManager::stopAll() {
    for (auto& [_, track] : m_tracks) {
        if (track->getStatus() == sf::SoundSource::Playing) {
            track->stop();
        }
    }
    m_currentTrack = nullptr;
}

void MusicManager::loadAndPlay(const std::string& key, const std::string& filePath, bool loop) 
{
    loadTrack(key, filePath);
    play(key, loop);
}

void MusicManager::setMuted(bool mute) 
{
    m_muted = mute;
    if (mute) {
        stopAll();
    }
    else 
    {
        if (!m_lastTrackKey.empty()) {
            play(m_lastTrackKey, m_lastLoopState);
        }
    }
}

