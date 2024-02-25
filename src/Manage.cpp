#include "Manage.h"
 #include <iostream>


const std::string Manage::m_names[7] = { "Wall", "Door", "Key", "Present", "Cheese", "Mouse", "Cat" };
std::vector<sf::Texture> Manage::m_textures;
sf::Texture Manage::m_menuBack;
sf::Texture Manage::m_gameBack;
sf::Texture Manage::m_helpBack;
sf::Texture Manage::m_buttonBack;
//sf::Texture Manage::m_infoBack;
sf::Font Manage::m_font;


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
    // m_infoBack.loadFromFile("info.png");
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

 //sf::Texture* Manage::infoTexture()
 //{
 //    return &m_infoBack;
 //}


