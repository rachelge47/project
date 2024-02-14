#include "Menu.h"

void Menu::drawMenu( sf::RenderWindow& window) const
{
    for (auto& button : m_menu)
        button.drawButton(window);
}
