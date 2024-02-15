#include "Menu.h"

Menu::Menu()
{
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "error loading font";
		return;
	}
	
	//3 times in function
	sf::Text text("Help", font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color(72, 23, 100));

	HelpButton helpButton(text);
	//helpButton.setPosition(position);
	m_menu.push_back(helpButton);

}
void Menu::drawMenu( sf::RenderWindow& window) const
{
    for (auto& button : m_menu)
        button.drawButton(window);
}

void Menu::fillText()
{
	//for (const auto& str : { "Help", "Exit", "NewGame" })
	//{
	//	sf::Text text(str, m_font);
	//	text.setCharacterSize(24);
	//	text.setFillColor(sf::Color(72,23,100));

	//	m_titles.push_back(text);  //fill the text vetor 
	//}
}