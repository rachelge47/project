
#include "Menu.h"

Menu::Menu()
{
    sf::Vector2f position = { INIT_POS };

    sf::Text text = makeButton("New Game", Manage::getInstance().getFont());   //make four buttons
    m_menu.push_back(std::make_unique<StartButton>(text, position));

    position.y += m_menu[0]->getSize() + R_SPACE;
    text = makeButton("Help", Manage::getInstance().getFont());
    m_menu.push_back(std::make_unique<HelpButton>(text, position));

	position.y += m_menu[0]->getSize() + R_SPACE;
	text = makeButton("Exit", Manage::getInstance().getFont());
	m_menu.push_back(std::make_unique<ExitButton>(text, position));

	position = { MUTE_POS };
	text = makeButton("Music", Manage::getInstance().getFont());
	m_menu.push_back(std::make_unique<ExitButton>(text, position));
}

sf::Text Menu::makeButton(const std::string& str, const sf::Font* font)
{
    sf::Text text(str, *font);
    text.setCharacterSize(M_TEXT_SIZE);
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
		if (button->isClick(location))  //check on which button were the click
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

