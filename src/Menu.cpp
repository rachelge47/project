
#include "Menu.h"

Menu::Menu()
{
    sf::Vector2f position = { 700, 100 };

    sf::Text text = makeButton("New Game", Manage::getFont());
    m_menu.push_back(std::make_unique<StartButton>(text, position));

    position.y += m_menu[0]->getSize() + 20;
    text = makeButton("Help", Manage::getFont());
    m_menu.push_back(std::make_unique<HelpButton>(text, position));

	position.y += m_menu[0]->getSize() + 20;
	text = makeButton("Exit", Manage::getFont());
	m_menu.push_back(std::make_unique<ExitButton>(text, position));

	position = { 20,40 };
	text = makeButton("Music", Manage::getFont());
	m_menu.push_back(std::make_unique<ExitButton>(text, position));

}

sf::Text Menu::makeButton(const std::string& str, const sf::Font* font)
{
    sf::Text text(str, *font);
    text.setCharacterSize(65);
    text.setFillColor(sf::Color::Black);

    return text;
}

void Menu::drawMenu(sf::RenderWindow& window, const sf::Vector2f& mousePosition) const
{
    for (const auto& button : m_menu)
        button->drawButton(window, mousePosition);
}

std::string Menu::isClickMenu(const sf::Vector2f& location) const
{
	for (auto& button : m_menu)
	{
		if (button->isClick(location))
		{
			if (button->getText().getString() == "Help")
			{
				return "help";
			}
			else if (button->getText().getString() == "Exit")
			{
				return "exit";
			}
			else if (button->getText().getString() == "New Game")
			{
				return "newGame";
			}
			else if (button->getText().getString() == "Music")
			{
				return "Music";
			}

		}
	}
	return "not clicked";
}

