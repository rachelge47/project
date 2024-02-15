#include "Button.h"

Button::Button (const sf::Text& text)
	:m_text(text)
{
	m_button.setSize({ 50,100 });
	m_button.setFillColor(sf::Color(217, 173, 242));  //set color of button
	m_button.setOutlineThickness(5);
	m_button.setOutlineColor(sf::Color::Black);	
}


void Button::drawButton(sf::RenderWindow& window) const
{
	window.draw(m_button);
}


//void Button::getFont()
//{
//	if (!m_font.loadFromFile("arial.ttf"))
//	{
//		std::cout << "error loading font";
//		return;
//	}
//}


//void Button::fillText()
//{
//	for (const auto& str : { "Help", "Exit", "NewGame" })
//	{
//		sf::Text text(str, m_font);
//		text.setCharacterSize(24);
//		text.setFillColor(sf::Color(72,23,100));
//
//		m_titles.push_back(text);  //fill the text vetor 
//	}
//}

void HelpButton::action()
{
	GameControl::getInstance()->helpScreen();
}

void ExitButton::action()
{
	GameControl::getInstance()->exitGame();
}

void NewGameButton::action()
{
	GameControl::getInstance()->newGame();
}

