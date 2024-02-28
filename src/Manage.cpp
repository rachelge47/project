#include "Manage.h"
 #include <iostream>

const std::string Manage::m_names[7] = { "Wall", "Door", "Key", "Present", "Cheese", "Mouse", "Cat" };
const std::string Manage::m_soundNames[9] = { "catWithMouse", "eatCheese", "gameOver", "levelComplite", "loseLevel", "openDoor", "present", "win", "timeOut"};
std::vector<sf::Texture> Manage::m_textures;
//std::vector<sf::Sound> Manage::m_sounds;
sf::Sound Manage::m_sound;
std::vector<sf::SoundBuffer> Manage::m_soundBuffers;
sf::Texture Manage::m_menuBack;
sf::Texture Manage::m_gameBack;
sf::Texture Manage::m_helpBack;
sf::Texture Manage::m_buttonBack;
sf::Texture Manage::m_infoBack;
sf::Texture Manage::m_muteButton;
sf::Font Manage::m_font;
sf::Music Manage::m_music;

//void Manage::fillSoundVector()
//{
//    for (int i = 0; i < 8; i++)
//    {
//        sf::SoundBuffer soundBuff;
//        sf::Sound sound;
//
//        if (!soundBuff.loadFromFile(m_soundNames[i] + ".wav"))
//            exit(EXIT_FAILURE);
//
//        //sound.setBuffer(soundBuff);
//       // sound.setVolume(20);
//
//        m_sounds.push_back(sound);
//    }
//}

Manage::Manage()
{
}

void Manage::playMusic()
{
    m_music.openFromFile("music.wav");
    m_music.setVolume(30);
    m_music.setLoop(true);
    m_music.play();
}

void Manage::fillSoundVector()
{
    m_soundBuffers.resize(9);
    //m_sounds.resize(8);
    for (int i = 0; i < 9; i++)
    {
        if (!m_soundBuffers[i].loadFromFile(m_soundNames[i] + ".wav"))
            exit(EXIT_FAILURE);

        //m_sounds[i].setBuffer(m_soundBuffers[i]);
        //m_sounds[i].setVolume(30);
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

    const sf::SoundBuffer* soundBuffer = Manage::getSoundBuffer(soundIndex);
    //static sf::Sound sound;
    m_sound.setBuffer(*soundBuffer);
    m_sound.play();
    
    //sf::sleep(sf::milliseconds(100)); // Adjust the delay time as needed


    /*sf::Time offset = sf::seconds(0.2f);
    sound.setPlayingOffset(offset);*/
    //sf::sleep(sf::milliseconds(500)); // Adjust the delay time as needed

    return &m_sound;
}

void Manage::fillTexturVector()
{
    for (int i = 0; i < 7; i++)
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
   // window.display();
}

 void Manage::load()
 {
     m_menuBack.loadFromFile("backCatMouse.png");
     m_gameBack.loadFromFile("garssBack.png");
     m_helpBack.loadFromFile("HELP.png");
     m_buttonBack.loadFromFile("cheesebutton.png");
     m_muteButton.loadFromFile("mute.png");

 }



 void Manage::load1()
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


