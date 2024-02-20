#include "Menu.h"

Menu::Menu()
{
	
	if (!m_font.loadFromFile("C:/Windows/Fonts/lucon.ttf"))
	{
		std::cout << "error loading font";
		return;
	}
	
	sf::Vector2f position = {800,50};
	
	sf::Text text= makeButton("Start", m_font);
	m_menu.push_back(std::make_unique<StartButton>(text, position));

	position.y += m_menu[0]->getSize() + 50;
	text = makeButton("Help", m_font);
	m_menu.push_back(std::make_unique<HelpButton>(text, position));

	position.y += m_menu[0]->getSize() + 50;
	text = makeButton("Exit", m_font);
	m_menu.push_back(std::make_unique<ExitButton>(text,position));

	position.y += m_menu[0]->getSize() + 50;
	text = makeButton("New Game", m_font);
	m_menu.push_back(std::make_unique<NewGameButton>(text,position));

}

sf::Text Menu:: makeButton(const std::string &str,const sf::Font &font)
{
	sf::Text text(str, font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);

	return text;
}


void Menu::drawMenu( sf::RenderWindow& window) const
{
    for (auto& button : m_menu)
        button->drawButton(window);
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
			else if (button->getText().getString() == "Start")
			{
				return "start";
			}
		}
	}
	return "not clicked";
}

