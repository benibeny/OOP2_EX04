#include "SoundManager.h"
#include <stdexcept>
#include <algorithm>

SoundManager& SoundManager::getInstance() {
    static SoundManager instance;
    return instance;
}

void SoundManager::loadEffect(const std::string& key, const std::string& filePath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filePath)) {
        throw std::runtime_error("Failed to load sound effect: " + filePath);
    }
    m_buffers[key] = std::move(buffer);
}

void SoundManager::play(const std::string& key) {
    if (m_muted)
        return;

    auto it = m_buffers.find(key);
    if (it == m_buffers.end()) {
        throw std::runtime_error("Sound buffer not found for key: " + key);
    }

    auto sound = std::make_unique<sf::Sound>();
    sound->setBuffer(it->second);
    sound->setVolume(30);       
    sound->play();


    m_activeSounds.push_back(std::move(sound));

    // Optional cleanup: remove finished sounds
    m_activeSounds.erase(
        std::remove_if(m_activeSounds.begin(), m_activeSounds.end(),
            [](const std::unique_ptr<sf::Sound>& s) {
                return s->getStatus() == sf::Sound::Stopped;
            }),
        m_activeSounds.end()
    );
}



void SoundManager::initialize() 
{
    loadEffect("eat", "eat.ogg");
    loadEffect("diamond", "diamond.ogg");
    loadEffect("drop", "DROPFOOD.ogg");
    loadEffect("shot", "shot.ogg");             
    loadEffect("alienEat", "alienEat.ogg");
    loadEffect("roar", "ROAR3.ogg");
    loadEffect("deadBoss", "nikoopen.ogg");
    loadEffect("buttonclick", "buttonclick.ogg");
    loadEffect("buy", "BUY.ogg");
    loadEffect("buzzer", "BUZZER.ogg");
    loadEffect("die", "DIE.ogg");
    loadEffect("hatch", "DIE.ogg");
    loadEffect("splash", "DIE.ogg");
}
