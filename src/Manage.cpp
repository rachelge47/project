#include "Manage.h"
 #include <iostream>


const std::string Manage::m_names[7] = { "Wall", "Door", "Key", "Present", "Cheese", "Mouse", "Cat" };
std::vector<sf::Texture> Manage::m_textures;


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
    sf::Texture back;
    sf::Sprite background;
    back.loadFromFile(backName + ".png");
    background.setTexture(back);
    window.draw(background);
}