#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include <memory>

class MusicManager {
public:
    static MusicManager& getInstance();

    void loadTrack(const std::string& key, const std::string& filePath);
    void play(const std::string& key, bool loop = true);
    void stopCurrent();
    void stopAll();
    void loadAndPlay(const std::string& key, const std::string& filePath, bool loop = false);

private:
    MusicManager() = default;
    ~MusicManager() = default;

    MusicManager(const MusicManager&) = delete;
    MusicManager& operator=(const MusicManager&) = delete;

    std::map<std::string, std::unique_ptr<sf::Music>> m_tracks;
    sf::Music* m_currentTrack = nullptr;
};

