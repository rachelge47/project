#include "Menu.h"

Menu::Menu()
{
	
	//m_font;
	if (!m_font.loadFromFile("C:/Windows/Fonts/lucon.ttf"))
	{
		std::cout << "error loading font";
		return;
	}
	
	sf::Vector2f position = {50,80};
	
	sf::Text text= makeButton("Help", m_font);
	//HelpButton helpButton(text);
	//helpButton.setPosition(position);
	m_menu.push_back(std::make_unique<HelpButton>(text, position));

	position.y += m_menu[0]->getSize() + 50;
	text = makeButton("Exit", m_font);
	//ExitButton exitButton(text);
	//exitButton.setPosition(position);
	m_menu.push_back(std::make_unique<ExitButton>(text,position));

	position.y += m_menu[0]->getSize() + 50;
	text = makeButton("New Game", m_font);
	//NewGameButton newGameButton(text);
	//newGameButton.setPosition(position);
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

bool Menu::isClickMenu(const sf::Vector2f& location) const
{
	for (auto& button : m_menu)
	{
		if (button->isClick(location))
		{
			return true;
		}
	}
	return false;
}

