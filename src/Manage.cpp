#include "Manage.h"
 #include <iostream>


Manage::Manage()
    : m_names{ "Wall", "Door", "Key", "Present", "Cheese", "Mouse", "Cat", "OVER", "youWin" },
    m_soundNames{ "catWithMouse", "eatCheese", "gameOver", "levelComplite", "loseLevel", "openDoor", "present", "win", "timeOut" }
{}

Manage* Manage::m_instance = nullptr;

Manage* Manage::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new Manage();
    }
    return m_instance;
}

void Manage::playMusic()
{
    m_music.openFromFile("music.wav");
    m_music.setVolume(VOLUME);
    m_music.setLoop(true);
    m_music.play();
}

void Manage::fillSoundBufVector()
{
    m_soundBuffers.resize(NUM_OF_NAMES);
    for (int i = 0; i < m_soundBuffers.size(); i++)
    {
        if (!m_soundBuffers[i].loadFromFile(m_soundNames[i] + ".wav"))
            exit(EXIT_FAILURE);
    }
}

sf::SoundBuffer* Manage:: getSoundBuffer(int index) 
{
    if (index < 0 || index >= m_soundBuffers.size())
    {
        std::cerr << "Invalid sound index" << std::endl;
        return nullptr; // Indicate failure
    }
    return &m_soundBuffers[index];
}


sf::Sound* Manage::getSound(int soundIndex)
{
    const sf::SoundBuffer* soundBuffer = Manage::Manage::getSoundBuffer(soundIndex);
    m_sound.setBuffer(*soundBuffer);
    m_sound.play();
  
    return &m_sound;
}

void Manage::fillTexturVector()
{
    for (int i = 0; i < NUM_OF_NAMES; i++)
    {
        sf::Texture texture;
        texture.loadFromFile(m_names[i] + ".png");
        m_textures.push_back(texture);
    }
}


void Manage::cover(sf::RenderWindow &window, const std ::string& backName)
{    
    sf::Sprite background;
    
    if (backName == "backCatMouse")
    {
        background.setTexture(m_menuBack);

    }

    else if (backName == "garssBack")
    {
        background.setTexture(m_gameBack);

    }
    else if (backName == "HELP")
    {
        background.setTexture(m_helpBack);

    }

    window.draw(background);
}

 void Manage::load()
 {
     m_menuBack.loadFromFile("backCatMouse.png");
     m_gameBack.loadFromFile("garssBack.png");
     m_helpBack.loadFromFile("HELP.png");
     m_buttonBack.loadFromFile("cheesebutton.png");
     m_muteButton.loadFromFile("mute.png");
     m_gameOver.loadFromFile("OVER.png");
     m_youWin.loadFromFile("youWin.png");
 }

 void Manage::loadBar()
 {    
     m_infoBack.loadFromFile("bar.png");
 }


 sf::Texture* Manage::buttonTexture()
 {
     return &m_buttonBack;
 }

 sf::Font* Manage::getFont()
 {
     if (!m_font.loadFromFile("Font.otf"))
     {
         std::cout << "error loading font";
     }
     return &m_font;
 }

 sf::Texture* Manage::infoTexture()
 {
     return &m_infoBack;
 }


