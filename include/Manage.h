#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Macros.h"

//a singltone class to load and save all textures and sounds

class Manage {
public:

    static Manage& getInstance();
    void playMusic();
    void fillSoundBufVector();
    void fillTexturVector();
    void cover( sf::RenderWindow& window, const std::string& backName) const;
    sf::Texture *getTexture(int index) { return &m_textures[index]; }
    sf::Sound* getSound(int index);
    sf::Music& getMusic() { return m_music; }
    void stopMusic() { m_music.pause(); }
    void startMusic() { m_music.play(); }
    sf::SoundBuffer* getSoundBuffer(int index);
    void load();
    void loadBar();
    sf::Texture* buttonTexture();
    sf::Font* getFont();
    sf::Texture* infoTexture();
   
    //~Manage() { delete m_instance; }

private:
    Manage();
    std::vector<sf::Texture> m_textures;
    sf::Sound m_sound;
    std::vector<sf::SoundBuffer> m_soundBuffers;
    std::string m_names[10];
    std::string m_soundNames[9];
    sf::Texture m_menuBack;
    sf::Texture m_gameBack;
    sf::Texture m_helpBack;
    sf::Texture m_buttonBack;
    sf::Texture m_infoBack;
    sf::Texture m_muteButton;
    sf::Texture m_musicButton;
    sf::Texture m_gameOver;
    sf::Texture m_youWin;
    sf::Font m_font;
    sf::Music m_music;
    
};