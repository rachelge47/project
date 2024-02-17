#include "Button.h"
#include "GameControl.h"

Button::Button (const sf::Text& text, const sf::Vector2f &position)
	:m_text(text), m_position(position)
{
	m_button.setSize({ 150,50 });
	m_button.setFillColor(sf::Color(217, 173, 242));  //set color of button
	m_button.setOutlineThickness(5);
	m_button.setOutlineColor(sf::Color::Red);

}


void Button::drawButton(sf::RenderWindow& window) 
{
	setPosition(m_position);
	window.draw(m_button);
	window.draw(m_text);
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_button.setPosition(position);
	m_text.setPosition(m_button.getPosition() + sf::Vector2f(5, 5));
}


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

