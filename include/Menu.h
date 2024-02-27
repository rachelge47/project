#pragma once
#include "Button.h"
#include <vector>
#include "Manage.h"

class Menu {
public:
    Menu();

    void drawMenu(sf::RenderWindow& window, const sf::Vector2f& mousePosition) const;
    std::string isClickMenu(const sf::Vector2f& location) const;

private:
    sf::Text makeButton(const std::string& str, const sf::Font* font);

    std::vector<std::unique_ptr<Button>> m_menu; // Vector of buttons
};
