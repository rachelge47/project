#include "Menu.h"

void Menu::draw( sf::RenderWindow& window) const
{
    for (auto& button : m_menu)
        button.drawButton(window);
}
