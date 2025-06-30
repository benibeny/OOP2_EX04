#pragma once

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager {
public:
    static SoundManager& getInstance();

    void loadEffect(const std::string& key, const std::string& filePath);
    void play(const std::string& key);
    void initialize(); 

private:
    SoundManager() = default;
    std::unordered_map<std::string, sf::SoundBuffer> m_buffers;
    std::vector<sf::Sound> m_sounds; // Reusable sounds to allow multiple effects
    std::vector<std::unique_ptr<sf::Sound>> m_activeSounds;

};
