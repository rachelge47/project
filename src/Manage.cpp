#include "Manage.h"
 #include <iostream>

const std::string Manage::m_names[7] = { "Wall", "Door", "Key", "Present", "Cheese", "Mouse", "Cat" };
const std::string Manage::m_soundNames[8] = { "catWithMouse", "eatCheese", "gameOver", "levelComplite", "loseLevel", "openDoor", "present", "win"};
std::vector<sf::Texture> Manage::m_textures;
std::vector<sf::Sound> Manage::m_sounds;
std::vector<sf::SoundBuffer> Manage::m_soundBuffers;
sf::Texture Manage::m_menuBack;
sf::Texture Manage::m_gameBack;
sf::Texture Manage::m_helpBack;
sf::Texture Manage::m_buttonBack;
sf::Texture Manage::m_infoBack;
sf::Font Manage::m_font;

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

void Manage::fillSoundVector()
{

    for (int i = 0; i < 8; i++)
    {
        sf::SoundBuffer soundBuff;

        if (!soundBuff.loadFromFile(m_soundNames[i] + ".wav"))
        {
            // Handle loading failure, e.g., print an error message
            std::cerr << "Failed to load sound: " << m_soundNames[i] << std::endl;
        }
        else
        {
            m_soundBuffers.push_back(soundBuff);
        }
    }
}


sf::Sound *Manage::getSound(int soundIndex)
{
    sf::Sound sound;
    
    sound.setBuffer(m_soundBuffers[soundIndex]);
    sound.setVolume(20); // Adjust the volume as needed
   
    return &sound;
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


